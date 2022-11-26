## Genel Olarak ROS2 Başlangıç Denemeleri

---------------------------

ROS paketlerinde **std::placeholders** yazdığımız yerlerde  aslında yer ayırmış oluruz yani callBack fonksiyonumuz bir parametre gerekiyorsa onun için yer ayırmış oluruz eğer yer ayırmak yerine doğrudan bir değer girmek isteyebiliriz ayırdığımız yerlere  o zaman direkt değerler girilebilir. (Örnek service_client_opp_cpp ve service_server_cpp)