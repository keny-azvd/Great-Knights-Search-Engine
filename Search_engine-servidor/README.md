Os pré-requisitos são a biblioteca boost instalada (veja no site oficial deles como instalar em seu sistema)

Dela utilizamos os pacotes boost_filesystem boost_thread pthread e boost_system.

Você deve compilar servidor.cpp linkando todos esses pacotes do boost

No linux o comando é:

g++ servidor.cpp -I /usr/include -lboost_filesystem -lboost_thread -lpthread -lboost_system

Após isso execute ./a.out e ele irá contruir a árvore de disponibilizar a página de buscas em localhost:8080/index.html
