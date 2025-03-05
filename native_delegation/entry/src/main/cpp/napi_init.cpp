#include "napi/native_api.h"
#include <cstdlib>
#include "hilog/log.h"

static napi_value DoLeak(napi_env env, napi_callback_info info){
    size_t argc = 1;
    napi_value args[1];
    // 获取ArkTS侧入参
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    // 获取全局对象，这里用global是因为napi_call_function的第二个参数是JS函数的this入参。
    napi_value global = nullptr;
    napi_get_global(env, &global);
    // 调用ArkTS方法
    napi_value result = nullptr;
    // 调用napi_call_function时传入的argv的长度必须大于等于argc声明的数量，且被初始化成nullptr
    napi_call_function(env, global, args[0], argc, args, &result);

    
    char* str = (char*) malloc(256);
    napi_get_value_string_utf8(env, result, str, 256, nullptr);
    OH_LOG_INFO(LOG_APP, "Oops! there is %{public}d leak: %{public}s", 1, str);
}

EXTERN_C_START
static napi_value Init(napi_env env, napi_value exports)
{
    napi_property_descriptor desc[] = {
        { "doLeak", nullptr, DoLeak, nullptr, nullptr, nullptr, napi_default, nullptr }
    };
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
