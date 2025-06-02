import { AbilityConstant, UIAbility, Want } from '@kit.AbilityKit';
import testNapi from 'libentry.so';
import geoLocationManager from '@ohos.geoLocationManager';
import { hilog } from '@kit.PerformanceAnalysisKit';

function getLastLocationString(): string{
  return JSON.stringify(geoLocationManager.getLastLocation()); //source
}

function delegationInArkTs(): void{
  let taint = JSON.stringify(geoLocationManager.getLastLocation()); //source
  hilog.info(0x0001, 'EntryAbility', "Oops! there is a leak in arkts: %{public}s", taint);
}

export default class EntryAbility extends UIAbility {

  onCreate(want: Want, launchParam: AbilityConstant.LaunchParam): void {

    testNapi.callSourceAndLeak(getLastLocationString);
    testNapi.callFunction(delegationInArkTs);

  }

};
