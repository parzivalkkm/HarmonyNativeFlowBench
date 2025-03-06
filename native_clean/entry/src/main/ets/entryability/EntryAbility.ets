import { AbilityConstant, UIAbility, Want } from '@kit.AbilityKit';

import geoLocationManager from '@ohos.geoLocationManager';
import { hilog } from '@kit.PerformanceAnalysisKit';
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
    let info = JSON.stringify(geoLocationManager.getLastLocation()); //source
    const data = new LastLocationData(info);
    testNapi.clean(data);
    hilog.info(0x0000, 'testTag', 'leak irrelevant data %{public}s', info);

    const data1 = new LastLocationData(info);
    testNapi.clean1(data1);
    hilog.info(0x0000, 'testTag', 'leak irrelevant data %{public}s', info);

    let info1 = JSON.stringify(geoLocationManager.getLastLocation()); //source

  }

};
