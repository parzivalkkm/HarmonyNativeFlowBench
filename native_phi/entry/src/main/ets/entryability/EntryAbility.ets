import { AbilityConstant, UIAbility, Want } from '@kit.AbilityKit';
import { hilog } from '@kit.PerformanceAnalysisKit';
import { window } from '@kit.ArkUI';
import geoLocationManager from '@ohos.geoLocationManager';
import testNapi from 'libentry.so';

export default class EntryAbility extends UIAbility {  onCreate(want: Want, launchParam: AbilityConstant.LaunchParam): void {
    
    // Source
    let info = JSON.stringify(geoLocationManager.getLastLocation());
    let str1 = "Hello ";
    let str2 = info;

    // 测试 contractPhiTest (字符串连接)

    let result = testNapi.contractPhiTest(str1, str2);
    hilog.info(0x0000, 'testTag', 'ContractPhiTest StrCat: str1 +str2 = %{public}s', result);

    // 测试 contractPhiLeakTest (字符串连接并泄漏)
    let result = testNapi.contractPhiLeakTest(str1, str2);
  

    // 测试 branchPhiTest
    let result = testNapi.branchPhiTest("Branch", "Test");
    hilog.info(0x0000, 'testTag', 'BranchPhiTest result: %{public}s', result);
  }

};
