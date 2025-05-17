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


function leakIntoLog(info1 : string, info2 : string){
  hilog.info(0x0000, 'testTag', 'info1: %{public}s info2: %{public}s', info1,info2);
}

function leakInfo1IntoLog(info1 : string, info2 : string){
  hilog.info(0x0000, 'testTag', 'info1: %{public}s info2: %{public}s', info1,info2);
}

export default class EntryAbility extends UIAbility {
  onCreate(want: Want, launchParam: AbilityConstant.LaunchParam): void {
    let leak = JSON.stringify(geoLocationManager.getLastLocation())
    const data = new LastLocationData(leak);
    let info = testNapi.objCallFunction(data,data.getLastLocation);
    hilog.info(0x0000, 'testTag', 'leak LastLocation %{public}s', info);

    // 测试调用有参数函数
    testNapi.callFunctionWith2Args(leakIntoLog, 'info1', leak);
    testNapi.callFunctionWith2Args(leakInfo1IntoLog, 'info1', leak);

    // 测试在native中读写object字段
    let data1 = new LastLocationData("info");
    testNapi.setNamedProperty(data1, "lastLocation", leak);
    hilog.info(0x0000, 'testTag', 'leak LastLocation %{public}s', testNapi.getNamedProperty(data1, "lastLocation"));

  }

};
