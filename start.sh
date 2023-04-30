#!/bin/bash

ip=$(hostname -I | awk '{print $1}')
echo "IP local: "$ip

# Lê o número de vezes por segundo que o programa deve ser executado
echo -n "Informe a taxa de clientes por segundo: "
read vezes_por_segundo

# Calcula o intervalo de tempo entre as execuções em microssegundos
intervalo=$(echo "scale=6; 1 / $vezes_por_segundo" | bc)
echo $intervalo

# Executa o programa indefinidamente com o intervalo de tempo calculado
while true; do
    # sleep $intervalo
    ./client "$ip" &
    sleep $intervalo
done