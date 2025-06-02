import { AbilityConstant, UIAbility, Want } from '@kit.AbilityKit';
import testNapi from 'libentry.so';
import geoLocationManager from '@ohos.geoLocationManager';
import { hilog } from '@kit.PerformanceAnalysisKit';

function getLastLocationString(): string{
  return JSON.stringify(geoLocationManager.getLastLocation()); //source
}

function leakInArkTsFunction(info: string){
  hilog.info(0x0000, 'testTag', 'leak in arkTs func %{public}s', info); //sink
}

export default class EntryAbility extends UIAbility {

  onCreate(want: Want, launchParam: AbilityConstant.LaunchParam): void {

    testNapi.callSourceAndLeak(getLastLocationString);
    testNapi.callSourceAndSink(getLastLocationString, leakInArkTsFunction);

  }

};
