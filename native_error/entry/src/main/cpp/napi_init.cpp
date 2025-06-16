#include "napi/native_api.h"

static napi_value CreateErrorWithTaintAndThrow(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[1] = {nullptr};

    napi_get_cb_info(env, info, &argc, args , nullptr, nullptr);
    // 代码中发生某些错误后，可执行以下操作抛出异常
    // 在Node-API环境中创建一个字符串，并将其存储在errorCode变量中
    napi_value errorCode = nullptr;
    napi_create_string_utf8(env, "throw errorCode", NAPI_AUTO_LENGTH, &errorCode);
    // 在Node-API环境中创建一个字符串，并将其存储在errorMessage变量中
    napi_value errorMessage = args[0];
    // 创建一个ArkTS对象error
    napi_value error = nullptr;
    napi_create_error(env, errorCode, errorMessage, &error);
    // 通过napi_throw接口将对象抛出
    napi_throw(env, error);
    return nullptr;
}


static napi_value ThrowErrorWithTaint(napi_env env, napi_callback_info info) {
    size_t argc = 1;
    napi_value args[1] = {nullptr};
    
    napi_get_cb_info(env, info, &argc, args , nullptr, nullptr);
    
    char* errorMessage = new char[256];
    napi_get_value_string_utf8(env, args[0], errorMessage, NAPI_AUTO_LENGTH, nullptr);
    
    // napi_throw_error抛出 错误
    napi_throw_error(env, "throw errorCode", errorMessage);
    return nullptr;
}
EXTERN_C_START
static napi_value Init(napi_env env, napi_value exports) {
    napi_property_descriptor desc[] = {{"createErrorWithTaintAndThrow", nullptr, CreateErrorWithTaintAndThrow, nullptr,
                                        nullptr, nullptr, napi_default, nullptr},
                                       {"throwErrorWithTaint", nullptr, ThrowErrorWithTaint, nullptr,
                                        nullptr, nullptr, napi_default, nullptr}};
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
