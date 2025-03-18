import { AbilityConstant, UIAbility, Want } from '@kit.AbilityKit';
import { hilog } from '@kit.PerformanceAnalysisKit';
import geoLocationManager from '@ohos.geoLocationManager';
import testNapi from 'libentry.so';

function getLastLocationString(){
  return JSON.stringify(geoLocationManager.getLastLocation()); //source
}

export default class EntryAbility extends UIAbility {
  onCreate(want: Want, launchParam: AbilityConstant.LaunchParam): void {
    let info = testNapi.callFunction(getLastLocationString);
    hilog.info(0x0000, 'testTag', 'leak LastLocation %{public}s', info);

  }

};
