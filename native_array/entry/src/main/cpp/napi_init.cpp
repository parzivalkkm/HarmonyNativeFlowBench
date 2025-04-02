#include "napi/native_api.h"
#include "hilog/log.h"

static napi_value NAPI_Global_leakArray0(napi_env env, napi_callback_info info) {
    size_t argc = 1;
    napi_value args[1] = {nullptr};

    napi_get_cb_info(env, info, &argc, args , nullptr, nullptr);
    
    bool isArray = false;
    napi_is_array(env, args[0], &isArray);
    if (isArray) {

        napi_value array0 = nullptr;
        napi_get_element(env, args[0], 0, &array0);
        
        char* str = new char[256];
        napi_get_value_string_utf8(env, array0, str, 0, nullptr);
        
        OH_LOG_INFO(LOG_APP, "Leak LastLocation %{public}s", str);
    }
}

static napi_value NAPI_Global_setArray1(napi_env env, napi_callback_info info) {
    size_t argc = 2;
    napi_value args[2] = {nullptr};

    napi_get_cb_info(env, info, &argc, args , nullptr, nullptr);
    
    bool isArray = false;
    napi_is_array(env, args[0], &isArray);
    if (isArray) {
        
        napi_set_element(env, args[0], 1, args[1]);
    }
}

EXTERN_C_START
static napi_value Init(napi_env env, napi_value exports) {
    napi_property_descriptor desc[] = {
        {"leakArray0", nullptr, NAPI_Global_leakArray0, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"setArray1", nullptr, NAPI_Global_setArray1, nullptr, nullptr, nullptr, napi_default, nullptr}};
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
