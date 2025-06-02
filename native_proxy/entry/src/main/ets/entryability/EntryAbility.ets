import { AbilityConstant, UIAbility, Want } from '@kit.AbilityKit';
import { hilog } from '@kit.PerformanceAnalysisKit';
import geoLocationManager from '@ohos.geoLocationManager';
import testNapi from 'libentry.so';

function proxyInArkTs(str: string): string {
  return str;
}

export default class EntryAbility extends UIAbility {
  onCreate(want: Want, launchParam: AbilityConstant.LaunchParam): void {
    let info = JSON.stringify(geoLocationManager.getLastLocation());
    let info1 = testNapi.proxy(info)
    hilog.info(0x0000, 'testTag', 'leak LastLocation passed by cpp proxy %{public}s', info1);

    let info2 = testNapi.proxy_copy(info);
    hilog.info(0x0000, 'testTag', 'leak LastLocation passed by cpp copy proxy %{public}s', info2);

    let info3 =  testNapi.proxy_by_call(proxyInArkTs, info);
    hilog.info(0x0000, 'testTag', 'leak LastLocation passed by cpp call arkts proxy %{public}s', info3);
  }

};
