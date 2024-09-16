# Sockets

## Alumno: von der Heyde Ian Padrón: 107638


## Para este trabajo se utiliza el codigo del repositorio sockets-en-cpp con licencia GPL v2
link del repositorio: https://github.com/eldipa/sockets-en-cpp


## Diagrama

![img](http://www.plantuml.com/plantuml/png/ZL8zZzim3DtpAuHC_O27xa5mG8T3boB0eREWavbOi3vSaKvwQE-_rmfjdI3OG3QIZo8VdzuJaeeqEhlhJ0i2t41lGX55ypeI85UrYTh2RZSetQiBYFspSY1-U89uLXhsGlpT2Q6jGXG9kgT2D0WgwauY_1x1Qy1FdwVwUsuzgOWGv-Qlhsy4ae94YiPVKckgMkFlrOIY7EulvZ7l1Q5VKtc3q7ThmDD2QOY1WWwMCvx7yGL8Aj_AOLfFCkrTECJH5w4yn-2aySD8KvNBJXc_mkeqBzjWbk6PMnUGl7AmY1UlHHPq3yJnJQ7KDY2qlDtCAJEe3g-M70u2_X3u5iNnoCznofA--TwaXCDBDUvbuWFniN7vEK_BqojzVWBTGkmtv7cvdvozr1C7-V8KTxsS01cYF2jZUILJK3Qd4VGrfunYS532PQwqXe5oTpTI6sxP0LdfwXQMP-CK1lCfyIhB_zpsf1-TrAv5pXObKL8e56wA_w_ykkPEjeNOVzkBBqrpJ45bbTMM4zEQBocXoXcvvT7NhCGQz9pilynTVVM17lurJNL71LOqdy2texF_0G00)



Codigo PlantUML que genero ese diagrama:

```
@startuml
hide empty attributes
hide circle

package "Game Interface"  {
  class Game {
    -search_sequences()
  }
  class Parser {
    +byte_to_string()
    +line_to_bytes_parser()
  }
}

package "User Interface"  {
  class Client {
    -protocol
    -parser
    -get_and_print_line()
    +run()
    +run_from_input()

    +main()
  }
}

package "Protocol Interface"  {
  class Protocol {
    -hostname
    -servname
    -socket
    -was_closed
    +is_close()
  }
  class ClientProtocol {
    << extends >>
    +send_byte()
    +get_msg()
  }
  class ServerProtocol {
    << extends >>
    +send_msg()
    +get_byte()
  }
}

package "Network Interface"  {
  class Socket {
    -skt
    -closed
    -chk_skt_or_fail()
    +sendall()
    +recvall()
    +sendsome()
    +recvsome()
    +accept()
    +shutdown()
    +close()
  }
}

package "Server Interface"  {
  class Server {
    -srv_socket
    -protocol
    -parser
    -num_cmds
    -get_bytes_to_msg()
    -is_close()
    +run()
    
    +main()
  }
}

Client "1" *--> "1" ClientProtocol
Client "1" *--> "1" Parser
Server "1" *--> "1" ServerProtocol
Server "1" *--> "1" Parser
Server "1" *--> "1" Socket
Server "1" *--> "1" Game
Protocol "1" *--> "1" Socket

Protocol <|-- ClientProtocol
Protocol <|-- ServerProtocol
@enduml
```
http://www.plantuml.com/
