#include "Loading.h"
#include "DxLib.h"
#include <string>
#include <cstdio>

#include "Utility.h"

// ========================
// LoadSoundTask 実装
// ========================

LoadSoundTask::LoadSoundTask(const char* path)
    : m_path(path), m_handle(-1)
{}

int LoadSoundTask::Execute() {
    m_handle = LoadSoundMem(m_path);
    if (m_handle == -1) {
        // 読み込み失敗時はログなどに出しても良い
        char buf[256];
        //std::sprintf(buf, "Failed to load sound: %s", m_path);
        OutputDebugStringA(buf);
    }

    return m_handle;
}

const char* LoadSoundTask::GetTaskName() const {
    return m_path;
}

int LoadSoundTask::GetHandle() const {
    return m_handle;
}

// ========================
// InitializeSoundManagerTask 実装
// ========================

InitializeSoundManagerTask::InitializeSoundManagerTask() {}

int InitializeSoundManagerTask::Execute() {
    // サウンドマネージャーの初期化処理をここに書く
    // 今はダミーで待機だけ
    WaitTimer(100);

    return 0;
}

const char* InitializeSoundManagerTask::GetTaskName() const {
    return "Initialize Sound Manager";
}

// ========================
// InitializeSceneManagerTask 実装
// ========================

InitializeSceneManagerTask::InitializeSceneManagerTask() {}

int InitializeSceneManagerTask::Execute() {
    // シーンマネージャーの初期化処理をここに書く
    // 今はダミーで待機だけ
    WaitTimer(100);

    return 0;
}

const char* InitializeSceneManagerTask::GetTaskName() const {
    return "Initialize Scene Manager";
}

// ========================
// LoadingManager 実装
// ========================


void LoadingManager::AddTask(std::unique_ptr<ILoadTask> task) {
    m_tasks.push_back(std::move(task));
}



void LoadingManager::ExecuteAll() {
    const int total = static_cast<int>(m_tasks.size());

    for (int i = 0; i < total; ++i) {
        ClearDrawScreen();

        float progress = static_cast<float>(i) / total;

        // 進捗バーの描画
        const int barX = Utility::SCREEN_WIDTH / 2-200, barY = Utility::SCREEN_HEIGHT / 2, barWidth = 400, barHeight = 30;
        DrawBox(barX, barY, barX + barWidth, barY + barHeight, GetColor(255, 255, 255), FALSE);

        int filledWidth = static_cast<int>(barWidth * progress);
        DrawBox(barX, barY, barX + filledWidth, barY + barHeight, GetColor(100, 200, 255), TRUE);

        // ローディング文字列
        std::string loadingText = "Loading: ";
        loadingText += m_tasks[i]->GetTaskName();

        DrawString(Utility::SCREEN_WIDTH/2- 200, Utility::SCREEN_HEIGHT/2-40, loadingText.c_str(), GetColor(255, 255, 255));

        ScreenFlip();

        // タスク実行
        m_tasks[i]->Execute();

        // 少し待つ（UI更新時間）
        WaitTimer(100);
    }

    // 完了画面描画
    ClearDrawScreen();

   /* DrawBox(Utility::SCREEN_WIDTH/2- 200, Utility::SCREEN_HEIGHT / 2, , 420, GetColor(255, 255, 255), FALSE);
    DrawBox(Utility::SCREEN_WIDTH / 2- 200, Utility::SCREEN_HEIGHT / 2, 440 + 400, 420, GetColor(100, 200, 255), TRUE);*/

    DrawString(Utility::SCREEN_WIDTH / 2- 200, Utility::SCREEN_HEIGHT / 2, "Loading Complete!", GetColor(255, 255, 255));

    ScreenFlip();

    WaitTimer(300);
}

//タスク群から特定のハンドルを検索する
int LoadingManager::FindTaskHandle(std::string _filename)
{
    for (const auto& task : GetTasks())
    {
        if (std::string(task->GetTaskName()) == _filename)
        {
            return task->GetHandle();
        }
    }

    return -1;
}
