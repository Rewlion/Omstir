#pragma once

#include <core/types.h>
#include <core/utils/resizable_vector.hpp>
#include <core/utils/string_map.h>

#include <unordered_map>
#include <functional>

namespace fs
{
  class FilesWatcher
  {
  public:
    using Callback = std::function<void(string_view)>;

    static
    void init();
    
    static
    void shutdown();

    static
    void watchFileWrites(string_view filePath, Callback&& cb);

    static
    void readNotifies();

  private:
    static FilesWatcher* m_This;

    using watch_handle_t = void*;
    struct FileWatch
    {
      string path;
      Callback cb;
    };

    struct DirWatch
    {
      watch_handle_t handle = nullptr;
      std::vector<FileWatch> fileWatches;
    };

    utils::StringMap m_WatchedDirs;
    utils::ResizableVector<DirWatch, name_id_t> m_Watches;
  };
}