第一步: Makefile

VPATH:全局访问路径VAPTH:即在执行make命令时可以从该路径中查询目标和依赖make可识别一个特殊变量“VPATH”。通过变量“VPATH”可以指定依赖文件的搜索路径，
在规则的依赖文件在当前目录不存在时，make会在此变量所指定的目录下去寻找这些依赖文件。

1、“=”

      make会将整个makefile展开后，再决定变量的值。也就是说，变量的值将会是整个makefile中最后被指定的值。看例子：

            x = foo
            y = $(x) bar
            x = xyz

      在上例中，y的值将会是 xyz bar ，而不是 foo bar 。

2、“:=”

      “:=”表示变量的值决定于它在makefile中的位置，而不是整个makefile展开后的最终值。

            x := foo
            y := $(x) bar
            x := xyz

      在上例中，y的值将会是 foo bar ，而不是 xyz bar 了。

 
入口main ./tmk_core/protocol/lufa/lufa.c


```c keyboard_setup(); -> matrix_setup()->空;
    sleep_led_init();
    keyboard_init();
        timer_init(); 时间相关
        matrix_init(); 矩阵扫描相关
        backlight_init(); 背光相关
while(1){
        keyboard_task(); 进行键盘任务 //核心 需要分析
            matrix_scan() 
            action_exec(TICK);  action.c 核心2
                process_action(&record);
}
```


process_action(&record);代码
```c
action_t action = layer_switch_get_action(event);
switch
    |
    v
    register_code(action.key.code);
            add_key(code);      //action_util.c
                add_key_byte(key); ??// 6KRO_EAN
                    keyboard_report->keys[i] ??
            send_keyboard_report(); action_util.c
                host_keyboard_send(keyboard_report); host.c
                    (*driver->send_keyboard)(report);

```
```
action_t action = layer_switch_get_action(event);
||
||
VV

action_t layer_switch_get_action(event)   action.c
    action_for_key(layer,event.key) //event.key  row col keymap.c
        uint8_t keycode = keymap_key_to_keycode(layer, key);
        keycode_to_action(keycode);
            keycode_to_action 得到一个十六位的键值

```
action_t 是一种枚举啊类型,定义在action_code.h文件里,

layer = current_layer_for_key(event.key);


一个重要的函数
/* translates keycode to action */
static action_t keycode_to_action(uint8_t keycode)
