#pragma once
#include <string>
#include <vector>
#include <memory>

// ========== ILoadTaskインタフェース ==========
// ILoadTask はタスクの基底クラス（例）
class ILoadTask {
public:
    virtual ~ILoadTask() = default;
    virtual int Execute() = 0;
    virtual const char* GetTaskName() const = 0;
    virtual int GetHandle() const { return -1; }
};



// ========== サウンド読み込みタスク ==========
class LoadSoundTask : public ILoadTask {
public:
    explicit LoadSoundTask(const char* path);
    int Execute() override;
    const char* GetTaskName() const override;
    int GetHandle() const;
private:
    const char* m_path;
    int m_handle;
};

// ========== 初期化タスク ==========
class InitializeSoundManagerTask : public ILoadTask {
public:
    InitializeSoundManagerTask();
    int Execute() override;
    const char* GetTaskName() const override;
};

class InitializeSceneManagerTask : public ILoadTask {
public:
    InitializeSceneManagerTask();
    int Execute() override;
    const char* GetTaskName() const override;
};

// ========== ローディングマネージャー ==========
class LoadingManager {
private:
    std::vector<std::unique_ptr<ILoadTask>> tasks;
    std::vector<std::unique_ptr<ILoadTask>> m_tasks;

public:
    void AddTask(std::unique_ptr<ILoadTask> task);

    void ExecuteAll();

    // ここを追加
    const std::vector<std::unique_ptr<ILoadTask>>& GetTasks() const {
        return tasks;
    }

    int FindTaskHandle(std::string _filename);   //タスク群から特定のハンドルを検索する
};
