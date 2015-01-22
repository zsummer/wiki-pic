To help future visitors who may find this question,

here is a solution which works on `Linux`, `FreeBSD`, `OS X`, `NetBSD` and `Windows`:

    __attribute__((unused)) std::string *getFileContent(const std::string &file,
                                                        std::string &content) {
      std::ifstream f(file.c_str());
    
      if (!f.is_open())
        return nullptr;
    
      f.seekg(0, std::ios::end);
      auto len = f.tellg();
      f.seekg(0, std::ios::beg);
    
      if (len != static_cast<decltype(len)>(-1))
        content.reserve(static_cast<size_t>(f.tellg()));
    
      content.assign(std::istreambuf_iterator<char>(f),
                     std::istreambuf_iterator<char>());
    
      return &content;
    }
    
    const std::string &getParentProcessName() {
      static std::string name;
    #ifdef _WIN32
      HANDLE h = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
      PROCESSENTRY32 pe;
    
      auto zerope = [&]() {
        memset(&pe, 0, sizeof(pe));
        pe.dwSize = sizeof(PROCESSENTRY32);
      };
    
      zerope();
    
      auto pid = GetCurrentProcessId();
      decltype(pid) ppid = -1;
    
      if (Process32First(h, &pe)) {
        do {
          if (pe.th32ProcessID == pid) {
            ppid = pe.th32ParentProcessID;
            break;
          }
        } while (Process32Next(h, &pe));
      }
    
      if (ppid != static_cast<decltype(ppid)>(-1)) {
        PROCESSENTRY32 *ppe = nullptr;
        zerope();
    
        if (Process32First(h, &pe)) {
          do {
            if (pe.th32ProcessID == ppid) {
              ppe = &pe;
              break;
            }
          } while (Process32Next(h, &pe));
        }
    
        if (ppe) {
          char *p = strrchr(ppe->szExeFile, '\\');
          if (p) {
            name = p + 1;
          } else {
            name = ppe->szExeFile;
          }
        }
      }
    
      CloseHandle(h);
    
      if (!name.empty()) {
        return name;
      }
    #else
      auto getName = [](const char * path)->const char * {
        if (const char *p = strrchr(path, '/')) {
          return p + 1;
        }
        return path;
      };
      (void)getName;
      auto ppid = getppid();
    #ifdef __APPLE__
      char path[PROC_PIDPATHINFO_MAXSIZE];
      if (proc_pidpath(ppid, path, sizeof(path))) {
        name = getName(path);
        return name;
      }
    #elif defined(__FreeBSD__)
      struct kinfo_proc *proc = kinfo_getproc(ppid);
      if (proc) {
        name = getName(proc->ki_comm);
        free(proc);
        return name;
      }
    #else
      std::stringstream file;
      file << "/proc/" << ppid << "/comm";
      if (getFileContent(file.str(), name)) {
        if (!name.empty() && name.rbegin()[0] == '\n') {
          name.resize(name.size() - 1);
        }
        return name;
      } else {
        file.str(std::string());
        file << "/proc/" << ppid << "/exe";
        char buf[PATH_MAX + 1];
        if (readlink(file.str().c_str(), buf, sizeof(buf)) > 0) {
          buf[PATH_MAX] = '\0';
          name = getName(buf);
          return name;
        }
      }
    #endif
    #endif
      name = "unknown";
      return name;
    }
