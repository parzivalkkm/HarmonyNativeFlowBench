#include "napi/native_api.h"
#include "hilog/log.h"
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

static napi_value NAPI_Global_leak2File(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[1] = {nullptr};

    napi_get_cb_info(env, info, &argc, args , nullptr, nullptr);
    
    char* str = new char[256];
    napi_get_value_string_utf8(env, args[0], str, NAPI_AUTO_LENGTH, nullptr);
    
     int fd = open("/mnt/sdcard/info.txt", O_RDWR | O_CREAT, 0666);
    if (fd > 0) {
        write(fd, str, 256);
        close(fd);
    } else {
        OH_LOG_INFO(LOG_APP, "Leak LastLocation %{public}s", str);
    }
}

    static napi_value NAPI_Global_leak2Internet(napi_env env, napi_callback_info info) {
        size_t argc = 1;
        napi_value args[1] = {nullptr};
    
        napi_get_cb_info(env, info, &argc, args , nullptr, nullptr);
        
        char* str = new char[256];
        napi_get_value_string_utf8(env, args[0], str, NAPI_AUTO_LENGTH, nullptr);
        
        int sockFD, new_socket;
        char * message;
        if ((sockFD = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            OH_LOG_INFO(LOG_APP, "Leak LastLocation Socket Create Failed:%{public}s", strerror(errno));
            return nullptr;
        }
        if (connect(sockFD, (struct sockaddr *)&sockFD, sizeof(sockFD)) < 0) {
            OH_LOG_INFO(LOG_APP, "Leak LastLocation Connect Failed:%{public}s", strerror(errno));
            return nullptr;
        }
        if (write(sockFD, str, strlen(str)) <= 0) {
            OH_LOG_INFO(LOG_APP, "Leak LastLocation Write Failed:%{public}s", strerror(errno));
            return nullptr;
        }
        OH_LOG_INFO(LOG_APP, "Leak LastLocation %{public}s", str);
    }

EXTERN_C_START
static napi_value Init(napi_env env, napi_value exports) {
    napi_property_descriptor desc[] = {
        {"leak2File", nullptr, NAPI_Global_leak2File, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"leak2Internet", nullptr, NAPI_Global_leak2Internet, nullptr, nullptr, nullptr, napi_default, nullptr}};
    napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc);
    return exports;
}
EXTERN_C_END

static napi_module demoModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = Init,
    .nm_modname = "entry",
    .nm_priv = ((void*)0),
    .reserved = { 0 },
};

extern "C" __attribute__((constructor)) void RegisterEntryModule(void)
{
    napi_module_register(&demoModule);
}
