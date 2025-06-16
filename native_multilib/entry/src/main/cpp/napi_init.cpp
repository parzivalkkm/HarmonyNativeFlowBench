#include "napi/native_api.h"

static napi_value NAPI_Global_proxy(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value argv[1] = {nullptr};
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);
    
    return argv[0];
}

EXTERN_C_START
static napi_value Init(napi_env env, napi_value exports)
{
    
    napi_value fn = nullptr;
    napi_create_function(env, nullptr, 0, NAPI_Global_proxy, nullptr, &fn);
    napi_set_named_property(env, exports, "proxy", fn);
    
    return exports;
}
EXTERN_C_END

// https://developer.huawei.com/consumer/cn/forum/topic/0204155244605065198

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
