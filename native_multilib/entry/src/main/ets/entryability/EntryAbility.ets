import { AbilityConstant, UIAbility, Want } from '@kit.AbilityKit';
import { hilog } from '@kit.PerformanceAnalysisKit';
import geoLocationManager from '@ohos.geoLocationManager';
import testEntry from 'libentry.so';
import {leak} from 'libleak.so';

export default class EntryAbility extends UIAbility {
  onCreate(want: Want, launchParam: AbilityConstant.LaunchParam): void {
    let info = JSON.stringify(geoLocationManager.getLastLocation());
    let info1 = testEntry.proxy(info);
    hilog.info(0x0000, 'testTag', 'leak LastLocation passed by cpp proxy (libentry.so) %{public}s', info1);

    // 测试具名导入
    leak(info);

    // 测试动态加载模块
    let dynamicModule: ESObject = loadNativeModule("libentry.so");
    dynamicModule.leak(info);

  }


};
