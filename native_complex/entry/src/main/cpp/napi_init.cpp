#include "napi/native_api.h"

static napi_value ObjCallFunction(napi_env env, napi_callback_info info)
{
    // 获取ArkTS侧传递的两个参数
    size_t argc = 2;
    napi_value argv[2] = {nullptr};
    // 获取ArkTS侧入参
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);
    // 调用ArkTS方法
    napi_value result = nullptr;
    // 调用napi_call_function时传入的argv的长度必须大于等于argc声明的数量，且被初始化成nullptr
    napi_call_function(env, argv[0], argv[1], 0, nullptr, &result);
    return result;
}

static napi_value CallFunctionWith2Args(napi_env env, napi_callback_info info)
{
    // 获取ArkTS侧传递的两个参数
    size_t argc = 3;
    napi_value argv[3] = {nullptr};
    // 获取ArkTS侧入参
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);
    // 调用ArkTS方法
    napi_value result = nullptr;
    napi_value global = nullptr;
    napi_get_global(env, &global);
    // 调用napi_call_function时传入的argv的长度必须大于等于argc声明的数量，且被初始化成nullptr
    napi_call_function(env, global, argv[0], 2, &argv[1], &result);
    return result;
}

static napi_value SetNamedProperty(napi_env env, napi_callback_info info)
{

    size_t argc = 3;
    napi_value argv[3] = {nullptr};
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);
    napi_value result = nullptr;
    napi_set_property(env, argv[0], argv[1], argv[2]);
    return result;
}

static napi_value GetNamedProperty(napi_env env, napi_callback_info info)
{

    size_t argc = 2;
    napi_value argv[2] = {nullptr};
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);
    napi_value result = nullptr;
    napi_get_property(env, argv[0], argv[1], &result);
    return result;
}
EXTERN_C_START
static napi_value Init(napi_env env, napi_value exports)
{
    napi_property_descriptor desc[] = {
        { "objCallFunction", nullptr, ObjCallFunction, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "callFunctionWith2Args", nullptr, CallFunctionWith2Args, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "setNamedProperty", nullptr, SetNamedProperty, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "getNamedProperty", nullptr, GetNamedProperty, nullptr, nullptr, nullptr, napi_default, nullptr },
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
