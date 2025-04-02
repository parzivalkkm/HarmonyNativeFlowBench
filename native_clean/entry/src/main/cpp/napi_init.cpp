#include "napi/native_api.h"

static napi_value Clean(napi_env env, napi_callback_info info){
    size_t argc = 1;
    napi_value argv[1] = {nullptr};
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);
    napi_value newStr = nullptr;
    napi_create_string_utf8(env, "Cleaned!", NAPI_AUTO_LENGTH, &newStr);
    napi_value key = nullptr;
    napi_create_string_utf8(env, "lastLocation", NAPI_AUTO_LENGTH, &key);
    napi_set_property(env , argv[0], key, newStr);
}

static napi_value Clean1(napi_env env, napi_callback_info info){
    size_t argc = 1;
    napi_value argv[1] = {nullptr};
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);
    napi_value newStr = nullptr;
    napi_create_string_utf8(env, "Cleaned again!", NAPI_AUTO_LENGTH, &newStr);
    napi_set_named_property(env , argv[0], "lastLocation", newStr);
}

static void cleanStringInAnotherFunction(napi_env env, napi_value* ori) {
    napi_create_string_utf8(env, "Cleaned again!", NAPI_AUTO_LENGTH, ori);
}

static napi_value NAPI_Global_cleanString(napi_env env, napi_callback_info info) {
    size_t argc = 1;
    napi_value argv[1] = {nullptr};
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);
    cleanStringInAnotherFunction(env, &argv[0]);
    return argv[0];
}

EXTERN_C_START
static napi_value Init(napi_env env, napi_value exports) {
    napi_property_descriptor desc[] = {
        {"clean", nullptr, Clean, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"clean1", nullptr, Clean1, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"cleanString", nullptr, NAPI_Global_cleanString, nullptr, nullptr, nullptr, napi_default, nullptr}};
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
