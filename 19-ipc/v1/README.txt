NOTA:

Esta versão inclui uma implementação de "memchannel" que suporta acesso concorrente de apenas dois processos, em que um é o consumidor e outro é o produtor.

A utilização simultânea de vários produtores ou de vários consumidores não está devidamente acautelada.

Em mc_put, no momento em que é feito sem_post para o semáforo has_items não é garantido que todas as posições anteriores do array items estejam já preenchidas (os respectivos memcpy podem ainda estar a decorrer ou nem ter começado).

Em mc_get, no momento em que é feito sem_post para o semáforo has_space não é garantido que todas as posições anteriores do array items já estejam livres (os respectivos memcpy podem ainda estar a decorrer ou nem ter começado).
