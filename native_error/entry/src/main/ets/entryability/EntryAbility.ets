import { AbilityConstant, UIAbility, Want } from '@kit.AbilityKit';
import { hilog } from '@kit.PerformanceAnalysisKit';
import geoLocationManager from '@ohos.geoLocationManager';
import testNapi from 'libentry.so';

export default class EntryAbility extends UIAbility {
  onCreate(want: Want, launchParam: AbilityConstant.LaunchParam): void {
    let info = JSON.stringify(geoLocationManager.getLastLocation()); //source

    try {
      testNapi.createErrorWithTaintAndThrow(info);
    } catch (error) {
      // sink
      hilog.error(0x0000, 'testTag', 'Test Node-API napi_throw errorCode: %{public}s, errorMessage: %{public}s', error.code, error.message);
    }

    try {
      testNapi.throwErrorWithTaint(info);
    } catch (error) {
      // sink
      hilog.error(0x0000, 'testTag', 'Test Node-API napi_throw_error errorCode: %{public}s, errorMessage: %{public}s', error.code, error.message);
    }

  }
};
