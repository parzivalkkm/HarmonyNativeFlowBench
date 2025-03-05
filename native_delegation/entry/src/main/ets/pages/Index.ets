@Entry
@Component
struct Index {
  @State message: string = 'Hello World';

  test() {
    this.message = 'test';
  }

  build() {
    RelativeContainer() {
      Text(this.message)
        .id('HelloWorld')
        .fontSize(50)
        .fontWeight(FontWeight.Bold)
        .alignRules({
          center: { anchor: '__container__', align: VerticalAlign.Center },
          middle: { anchor: '__container__', align: HorizontalAlign.Center }
        })
      Button('press').onClick(() => this.test());
      Button('press1').onClick(() => {
        this.message = 'test';
      });
    }
    .height('100%')
    .width('100%')
  }
}