import { AbilityConstant, UIAbility, Want } from '@kit.AbilityKit';
import geoLocationManager from '@ohos.geoLocationManager';
import testNapi from 'libentry.so';
import { hilog } from '@kit.PerformanceAnalysisKit';

export default class EntryAbility extends UIAbility {
  onCreate(want: Want, launchParam: AbilityConstant.LaunchParam): void {
    let arr = ["", "", "", "", ""]
    let info = JSON.stringify(geoLocationManager.getLastLocation()); //source
    arr[0] = info;
    testNapi.leakArray0(arr);

    let arr1 = ["", "", "", "", ""]
    testNapi.setArray1(arr1,info)
    let taintedData = arr1[1]
    hilog.info(0x0000, 'testTag', 'leak LastLocation %{public}s', taintedData);
    let untaintedData = arr1[0]
    hilog.info(0x0000, 'testTag', 'leak LastLocation %{public}s', untaintedData);
  }

};
