入口函数: driver/main.c

keyboard_task()  进行键盘任务           @keyboard.c
 ├─ matrix_scan()[`debouncing`]   矩阵扫描            @matrix.c
 └─ action_exec(e)  进行'按键'处理          @action.c
    │  //分支
    ├─ process_action(&record);
    └─ action_tapping_process(record);  //执行了这个
      └─ process_tapping(&record)       @action_tapping.c
         └─ process_action()            @action.c
            │
            ├─ action_t action = layer_switch_get_action(event)
            └─ switch
               └─ register_code(action.key.code)
                  └─ add_key(code)
                     └─ add_key_byte(code)
                        └─ 6KRO_ENABLE
                           └─ send_keyboard_report

