#include "napi/native_api.h"
#include <cstdlib>


static napi_value NAPI_Global_proxy(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value argv[1] = {nullptr};
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);
    
    return argv[0];
}
static napi_value NAPI_Global_proxy_copy(napi_env env, napi_callback_info info) {
    size_t argc = 1;
    napi_value argv[1] = {nullptr};
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);
    char* str = (char*) malloc(256);
    napi_get_value_string_utf8(env, argv[0], str, 256, nullptr);
    napi_value ret = nullptr;
    napi_create_string_utf8(env, str, 256, &ret);
    return ret;
}
EXTERN_C_START
static napi_value Init(napi_env env, napi_value exports) {
    napi_property_descriptor desc[] = {
        {"proxy", nullptr, NAPI_Global_proxy, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"proxy_copy", nullptr, NAPI_Global_proxy_copy, nullptr, nullptr, nullptr, napi_default, nullptr}};
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
