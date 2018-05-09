# UFPA Projetos 3: Intelligent Personal Assistant for Health.

## Cronograma

Tarefa/Datas | 05/04 | 12/04 | 19/04 | 26/04 | 03/05 | 10/05 | 15/05 | 17/05 | 22/05 | 24/05 | 29/05 | 31/05 | 05/06 | 07/06 | 12/06 | 14/06 | 19/06 |21/06 |
------------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|------|
Descrição inicial do projeto |x| | | | | | | | | | | | | | | | | |
Definição da IA |x| x| | | | | | | | | | | | | | | | |
Modelagem do Hardwarer |x| x| | | | | | | | | | | | | | | | |
Modelagem estética do hardware | | x| x| x| x| x| x| | | | | | | | | | | |
Impressão do modelo 3D | | | | | | | | | | | x| | | | | | | |
Teste inicial do IA no rapsberry 3 | | x| x| | | | | | | | | | | | | | | |
Estudo da Documentação da IA | | x| x| x| x| | | | | | | | | | | | | |
Estudo do Myoware | | | x| x| x| | | | | | | | | | | | | |
Criação de skills básicas para a saúde no mycroft | | | | | x| x| x| x| x| x| | | | | | | | |
Teste de componentes | | | | | | x| x| x| | | | | | | | | | |
Montagem do Hardware para teste (Pré-beta)| | | | | | | | x| x| x| | | | | | | | |
Montagem do PCB | | | | | | | | x| x| x| | | | | | | | |
Impressão do PCB | | | | | | | | | | | x| | | | | | | |
Montagem do Hardware (Beta) | | | | | | | | | | | x| x| | | | | | |
Testes Finais | | | | | | | | | | | | | | | x| x| x| x|

## Guidelines
    * Hardware: (Gustavo)
       - Microcontrolador: Raspberry pi 3 (Conter a IA para o projeto)
       - Myoware (análise de sinais EMG);
       - NFC (Armazenamento de dados do usuário);
       - Display lcd tft 1.8 128x126 (Interface de interação com o usuário);
       - Sensor de frequência cardíaca e Oxímetro (bem intuitivo).

    * Design: (Pablo)
       - Arte visual
            |- Modelagem em 3D;
            |- Obs: Colocar um LCD;

    * Software: (Camila)
        - Mobile App (?);
        - Intelligent Personal Assistant (IPA): Mycroft [https://mycroft.ai/]
            |- Definir as skills;
            |- Trocar linguagem para PT-BR

        - Database (Para as funcionalidades abaixo) -> Cloud;

    * Funcionalidades:
        - Agendamento de lembretes (Consultas, Medicamentos, Bebe water, Cultura saude)
            |- Medicamentos: Horários, Dosagem, Periodo (Duração); -> Banco de dados;
            |- Cultura saude: Práticas saudaveis diarias;

        - Monitoramento de parâmetros fisiológicos;
