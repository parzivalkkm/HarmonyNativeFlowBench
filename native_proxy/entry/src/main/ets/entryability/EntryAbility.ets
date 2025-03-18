import { AbilityConstant, UIAbility, Want } from '@kit.AbilityKit';
import { hilog } from '@kit.PerformanceAnalysisKit';
import geoLocationManager from '@ohos.geoLocationManager';
import testNapi from 'libentry.so';



export default class EntryAbility extends UIAbility {
  onCreate(want: Want, launchParam: AbilityConstant.LaunchParam): void {
    let info = JSON.stringify(geoLocationManager.getLastLocation());
    let info1 = testNapi.proxy(info)
    hilog.info(0x0000, 'testTag', 'leak LastLocation %{public}s', info1);

    let info2 = testNapi.proxy_copy(info);
    hilog.info(0x0000, 'testTag', 'leak LastLocation %{public}s', info2);
  }

};
