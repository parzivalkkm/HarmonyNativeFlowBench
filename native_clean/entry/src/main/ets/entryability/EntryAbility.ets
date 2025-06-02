import { AbilityConstant, UIAbility, Want } from '@kit.AbilityKit';

import geoLocationManager from '@ohos.geoLocationManager';
import { hilog } from '@kit.PerformanceAnalysisKit';
import testNapi from 'libentry.so';


class LastLocationData {
  lastLocation: string =  "";
}

export default class EntryAbility extends UIAbility {
  onCreate(want: Want, launchParam: AbilityConstant.LaunchParam): void {
    let info = JSON.stringify(geoLocationManager.getLastLocation()); //source
    let data: LastLocationData = {lastLocation: info};
    testNapi.setProperty(data, 'lastLocation', "clean");
    hilog.info(0x0000, 'testTag', 'leak irrelevant data %{public}s', data.lastLocation);

    const data1: LastLocationData = { lastLocation: info}
    testNapi.setNamedProperty(data1, "clean");
    hilog.info(0x0000, 'testTag', 'leak irrelevant data %{public}s', data1.lastLocation);

    let info1 = JSON.stringify(geoLocationManager.getLastLocation()); //source

  }

};
