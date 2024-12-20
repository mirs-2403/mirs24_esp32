void ros_setup(){
  //micro-rosのセッティング
  set_microros_transports();
  delay(500);

  allocator = rcl_get_default_allocator();

  //nodeの作成とros_domein_idの作成
  rosid_setup_humble();
  //rosid_setup_foxy();

  //サブスクライバ、パブリッシャー、サービスの宣言
  rclc_publisher_init_default(
    &enc_pub,
    &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32MultiArray),
    "/encoder"
  );

  rclc_publisher_init_default(
    &vlt_pub,
    &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Float64MultiArray),
    "/vlt"
  );

  rclc_publisher_init_default(
    &curr_vel_pub,
    &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Float64MultiArray),
    "/vel"
  );

  rclc_subscription_init_default(
    &cmd_vel_sub,
    &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(geometry_msgs, msg, Twist),
    "/cmd_vel"
  );
  
  rclc_subscription_init_default(
    &param_sub,
    &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(mirs_msgs, msg, BasicParam),
    "/params"
  );
  
  rclc_service_init_default(
    &update_srv,
    &node,
    ROSIDL_GET_SRV_TYPE_SUPPORT(mirs_msgs, srv, ParameterUpdate),
    "/esp_update"
  );

  rclc_service_init_default(
    &reset_srv,
    &node,
    ROSIDL_GET_SRV_TYPE_SUPPORT(mirs_msgs, srv, SimpleCommand),
    "/reset_encoder"
  );

  rclc_service_init_default(
    &jack_up_srv,
    &node,
    ROSIDL_GET_SRV_TYPE_SUPPORT(mirs_msgs, srv, SimpleCommand),
    "/jack_up"
  );

  rclc_service_init_default(
    &jack_down_srv,
    &node,
    ROSIDL_GET_SRV_TYPE_SUPPORT(mirs_msgs, srv, SimpleCommand),
    "/jack_down"
  );

  const uint32_t timer_timeout = 100;

  rclc_timer_init_default(
    &timer,
    &support,
    RCL_MS_TO_NS(timer_timeout),
    timer_callback
  );

  //イベント発生の設定（数字はイベントの発生点の数）
  //デフォルトの発生点はsubscriberが2(/cmd_vel,/params)、serviceが2(/reset,/update)、timerが1（定期実行）の合計5
  rclc_executor_init(&executor, &support.context, 7, &allocator);
  rclc_executor_add_subscription(&executor, &cmd_vel_sub, &cmd_vel_msg, &cmd_vel_Callback, ON_NEW_DATA);
  rclc_executor_add_subscription(&executor, &param_sub, &param_msg, &param_Callback, ON_NEW_DATA);
  rclc_executor_add_service(&executor, &update_srv, &update_req, &update_res, update_service_callback);
  rclc_executor_add_service(&executor, &reset_srv, &reset_req, &reset_res, reset_service_callback);
  rclc_executor_add_service(&executor, &jack_up_srv, &jack_up_req, &jack_up_res, jack_up_callback);
  rclc_executor_add_service(&executor, &jack_down_srv, &jack_down_req, &jack_down_res, jack_down_callback);
  rclc_executor_add_timer(&executor, &timer);
}

/*    ROS_DOMAIN_ID 設定用                  */
/*    foxyの場合はrosid_setup_foxy()        */
/*    humbleの場合はrosid_setup_humble()    */
void rosid_setup_foxy(){
  rcl_node_options_t node_ops;
  node_ops = rcl_node_get_default_options();
  //node_ops.domain_id = ROS_DOMAIN_ID;
  rclc_support_init(&support, 0, NULL, &allocator);
  rclc_node_init_with_options(&node, "ESP32_node", "", &support, &node_ops);
}

void rosid_setup_humble(){
  rcl_init_options_t init_options;
  init_options = rcl_get_zero_initialized_init_options();
  size_t domain_id = ROS_DOMAIN_ID;
  rcl_init_options_init(&init_options, allocator); // <--- This was missing on ur side
  // Set ROS domain id
  rcl_init_options_set_domain_id(&init_options, domain_id);
  // Setup support structure.
  rclc_support_init_with_options(&support, 0, NULL, &init_options, &allocator);
  // create node
  rclc_node_init_default(&node, "ESP32_node", "", &support);
}
