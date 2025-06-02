import { AbilityConstant, UIAbility, Want } from '@kit.AbilityKit';
import { hilog } from '@kit.PerformanceAnalysisKit';
import geoLocationManager from '@ohos.geoLocationManager';
import testNapi from 'libentry.so';

function leakInArkTsFunction(info: string){
  hilog.info(0x0000, 'testTag', 'leak in arkTs func %{public}s', info);
}

export default class EntryAbility extends UIAbility {
  onCreate(want: Want, launchParam: AbilityConstant.LaunchParam): void {
    let info = JSON.stringify(geoLocationManager.getLastLocation()); //source
    testNapi.leak(info);//sink, leak
    testNapi.leakByCall(leakInArkTsFunction, info);
  }
};