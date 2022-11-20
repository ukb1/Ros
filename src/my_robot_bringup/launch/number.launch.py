from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    ld = LaunchDescription()
    subscriber = Node(
        package = "topic_subscriber_cpp",
        executable = "subscriber_cpp",  #package ve executable gerekli olan parametrelerdir  hangi paketin çalıştırılacağını ayarlarız.
        name= "deneme_node",       # Node name değiştirmiş oluruz.
        remappings=[
            ("Publisher_Node","new_topic")    #Topic ismini değiştirmiş oluruz  ilk parametre eski topic name ikincisi yeni topic name 
        ]
    )
    publisher = Node(
        package= "topic_publisher_cpp",
        executable= "publisher_cpp"
     
    )
    
    _parameter = Node(
        package= "parameters_cpp",
        executable= "param_node",
         name= "deneme_node2", 
        remappings=[
            ("number","param_topic")
        ],
        parameters=[
            {"first_param":22}      # Parametrelere değer atamış oluruz
        ]
    )
    
    ld.add_action(subscriber)
    ld.add_action(publisher)
    ld.add_action(_parameter)
    
    
    
    return ld