import { AbilityConstant, UIAbility, Want } from '@kit.AbilityKit';
import testNapi from 'libentry.so';
import geoLocationManager from '@ohos.geoLocationManager';

function getLastLocationString(){
  return JSON.stringify(geoLocationManager.getLastLocation()); //source
}
export default class EntryAbility extends UIAbility {
  onCreate(want: Want, launchParam: AbilityConstant.LaunchParam): void {
    testNapi.doLeak(getLastLocationString);
  }

};
