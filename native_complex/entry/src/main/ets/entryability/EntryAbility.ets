import { AbilityConstant, UIAbility, Want } from '@kit.AbilityKit';
import { hilog } from '@kit.PerformanceAnalysisKit';
import geoLocationManager from '@ohos.geoLocationManager';
import testNapi from 'libentry.so';


class LastLocationData {
  lastLocation: string;

  constructor(a: string) {
    this.lastLocation = a;
  }

  getLastLocation(): string {
    return this.lastLocation;
  }
}


export default class EntryAbility extends UIAbility {
  onCreate(want: Want, launchParam: AbilityConstant.LaunchParam): void {
    let leak = JSON.stringify(geoLocationManager.getLastLocation())
    const data = new LastLocationData(leak);
    let info = testNapi.objCallFunction(data,data.getLastLocation);
    hilog.info(0x0000, 'testTag', 'leak LastLocation %{public}s', info);
  }

};
