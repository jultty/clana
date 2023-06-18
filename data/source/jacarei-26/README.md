## Observações

Filtrando todos os resultados para o município de Jacareí/SP, temos um
total de 33 arquivos com 8 prefixos diferentes:

| Nº | Categoria            | Arquivos |
|----|----------------------|----------|
| 1. | chuvas               |    12    |
| 2. | cotas                |     5    |
| 3. | curvadescarga        |     2    |
| 4. | PerfilTransversal    |     2    |
| 5. | qualagua             |     3    |
| 6. | ResumoDescarga       |     4    |
| 7. | sedimentos           |     1    |
| 8. | vazoes               |     4    |
|    |                      | Σ = 33   |

Consulta aos recursos disponíveis na página web da ANA permitem entender a que se refere cada prefixo:

- **cotas**: Cota, "Níveis de rios e reservatórios" (ANA, 2020), "nível da água de um rio" (ANA, 2016)
- **vazoes**: Vazão, "volume de água que atravessa a seção transversal de um
rio durante uma unidade de tempo" (ANA, 2021), "Quantidade de água que escoa em determinado período de tempo" (ANA, 2020), "volume de água que passa entre dois pontos por um dado período de tempo" (ANA, 2016)
- **qualagua**: Qualidade da água
- **chuvas**: Chuvas, "total precipitado por unidade de área em um determinado tempo" (ANA, 2016)
- **curvadescarg**: Curva de descarga, ou curva-chave, "correspondência entre cota e vazão" (ANA, 2016)
- **ResumoDescarga**: Nenhuma definição encontrada.
- **PerfilTransversal**: Nenhuma definição encontrada. Para **seção transversal**, "Define-se seção transversal como uma vista em corte do leito do curso d’água" (ANA, 2021) "[a seção transversal é] a seção plana de um curso de água perpendicular à direção do escoamento" (JACCON e CUDO, apud. ANA, 2021)
- **sedimentos**: Sedimentos, "medida da quantidade do sedimento transportado pelos cursos d’água, [...] A carga sólida medida se refere à argila, silte e areia transportada." (CARVALHO et al., 2000)

> De forma geral, as **vazões** são determinadas a partir de uma equação denominada **curva-chave**, que associa os valores de vazão com as cotas dos níveis d’água do rio. Portanto, uma curva-chave é a relação matemática que correlaciona as variáveis Cota e Vazão para uma determinada seção do curso d’água ou de qualquer estrutura hidráulica. (ANA, 2021)

> Quando a estação fluviométrica apresentar uma condição mista, em que coexistam controles hidráulicos de canal e de seção, deve ser traçado um **perfil transversal** para cada um dos controles hidráulicos observados. Destaca- se que para esse caso, o levantamento cartográfico deve ser conduzido em ambas as margens, seguindo as mesmas premissas observadas para os controles hidráulicos de canal e de seção. (ANA, 2021)

A análise dos arquivos mostra que cada categoria possui diferentes cabeçalhos, todos contudo começando com o mesmo padrão: "EstacaoCodigo;NivelConsistencia;".

A função utilitária atualmente implementada no programa usa apenas uma coluna a mais, `Data`, que está presente em todos os cabeçalhos à exceção da categoria curvadescarga (2 arquivos), que utiliza `PeriodoValidadeInicio;PeriodoValidadeFim;` para marcar o período das medições.

Apesar de uma redução na precisão, para o escopo deste trabalho a retirada da coluna data não deverá impactar na eficácia da função.

### Listagem completa

```
csv
├── chuvas_C_02345024.csv
├── chuvas_C_02345026.csv
├── chuvas_C_02345027.csv
├── chuvas_C_02345029.csv
├── chuvas_C_02345066.csv
├── chuvas_C_02345106.csv
├── chuvas_C_02345110.csv
├── chuvas_C_02345128.csv
├── chuvas_C_02345186.csv
├── chuvas_C_02345203.csv
├── chuvas_C_02345204.csv
├── chuvas_C_02346016.csv
├── cotas_C_58044000.csv
├── cotas_C_58096000.csv
├── cotas_C_58110001.csv
├── cotas_C_58110002.csv
├── cotas_C_58138000.csv
├── curvadescarga_C_58096000.csv
├── curvadescarga_C_58110002.csv
├── PerfilTransversal_C_58096000.csv
├── PerfilTransversal_C_58110002.csv
├── qualagua_C_58110002.csv
├── qualagua_C_58110010.csv
├── qualagua_C_58138500.csv
├── ResumoDescarga_C_58096000.csv
├── ResumoDescarga_C_58110000.csv
├── ResumoDescarga_C_58110002.csv
├── ResumoDescarga_C_58138000.csv
├── sedimentos_C_58096000.csv
├── vazoes_C_58096000.csv
├── vazoes_C_58110000.csv
├── vazoes_C_58110002.csv
└── vazoes_C_58138000.csv

1 directory, 33 files
```

## Referências

- ANA, 2020: <https://progestao.ana.gov.br/portal/progestao/destaque-superior/eventos/webinarios/cotas-de-alerta/1-monitoramento.pdf>
- <https://progestao.ana.gov.br/portal/progestao/destaque-superior/eventos/webinarios/cotas-de-alerta/3-definicao-de-valores-de-referencia.pdf>
- ANA, 2016: <https://capacitacao2.ana.gov.br/conhecerh/bitstream/ana/2259/1/_Apostila_Medindo_as_%c3%81guas_-_ANA.pdf>
- ANA, 2021: <https://www.gov.br/ana/pt-br/assuntos/monitoramento-e-eventos-criticos/monitoramento-hidrologico/orientacoes-manuais/documentos/manual-de-nivelamento>
- CARVALHO et al, 2000: <https://www.gov.br/ana/pt-br/assuntos/monitoramento-e-eventos-criticos/monitoramento-hidrologico/orientacoes-manuais/entidades/guia-praticas-sedimentometricas-aneel-2000.pdf>
