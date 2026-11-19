


-- 1. Mostrar el DNI y el nombre las personas junto con los datos de los inmuebles que
-- poseen actualmente (los han comprado y no los han vendido) y cuyo porcentaje
-- como propietario supere el 50%.
-- DNI NOMBRE |CODI METROS|DIRECCION

SELECT p.DNI , p.NOMBRE , i.CODI , i.METROS , i.DIRECCION 
FROM PERSONA p , PERINM p2 , INMUEBLE i 
WHERE p.DNI = p2.DNI AND i.CODI  = p2.CODI AND p2.PORCENTAJE > 50 AND p2.FVENTAINM IS NULL;


-- 2. Obtener el DNI y el nombre de las personas junto con el número de inmuebles que
-- han comprado, pero solo de aquellos que han comprado más de 2 inmuebles con
-- un porcentaje superior al 50%.
-- DNI NOMBRE Más de 2 inmuebles comprados |

SELECT p.DNI , p.NOMBRE, count(*) 
FROM PERSONA p , PERINM p2 
WHERE p.DNI = p2.DNI AND p2.PORCENTAJE > 50
GROUP BY p.DNI , p.NOMBRE 
HAVING COUNT(*) > 2;


-- 3. Obtener por cada persona el número de inmuebles que ha comprado junto con la
-- media de metros de los inmuebles (redondeado a 2 decimales). Mostrar solo
-- aquellas personas que tengan más de un inmueble.
-- DNI NOMBRE |Dirección completa | Número inmuebles | Media metros |

SELECT p.DNI , p.NOMBRE, p.DIRECCION , count(*) AS NUMERO_INMUEBLES, ROUND(AVG(i.METROS ),2) AS media_metros 
FROM PERSONA p , PERINM p2, INMUEBLE i 
WHERE p.DNI = p2.DNI  AND i.CODI = p2.CODI 
GROUP BY p.DNI , p.NOMBRE , p.DIRECCION 
HAVING COUNT(*) > 1;



-- 4. Mostrar el código de inmueble y su dirección junto con el número de propietarios
-- que tiene o ha tenido. Muestra el resultado de mayor a menor por el número de
-- propietarios.
-- CODI | DIRECCION |NUM_PROPIETARIOS|

SELECT p2.CODI , i.DIRECCION , count(*) AS num_propietarios
FROM PERSONA p , PERINM p2 , INMUEBLE i 
WHERE p.DNI = p2.DNI  AND i.CODI = p2.CODI
GROUP BY p2.CODI , i.DIRECCION 
ORDER BY NUM_PROPIETARIOS DESC ;



-- 5. Mostrar el DNI y nombre de las personas junto con el número total de acciones
-- que han comprado en algún momento y a cuántas empresas pertenecen dichas acciones.
-- DNI NOMBRE Total acciones | Empresas dueñas |



-- 6. Mostrar las empresas con más de un inversor distinto.
-- EMPRESA | NUM INVERSORES|



-- 7. Obtener por cada persona cuántos inmuebles y acciones ha vendido.
-- DNI NOMBRE | Inmuebles vendidos Acciones vendidas|



-- 8. Comprobar si existe alguna inconsistencia en los inmuebles que no están vendidos,
-- es decir, sus propietarios superan el 100% del porcentaje.
-- CODI | TOTAL_PORCENTAJE |



-- 9. Mostrar el código del inmueble, su dirección y el número de veces que ha sido
-- vendido, mostrar solo aquellos que hayan sido vendidos entre el 1 de enero de
-- 2022 y la fecha actual.
-- CODI | DIRECCION Veces vendido |



-- 10. Mostrar el DNI y nombre de las personas cuya diferencia entre la fecha mínima de
-- compra y la fecha máxima de venta de sus acciones sea superior a 2 años.
-- DNI NOMBRE | PRIMERA_COMPRA | ULTIMA_VENTA|



-- 11. Mostrar las empresas en las que se han realizado compras de sus acciones en al
-- menos dos años distintos, junto con el número total de operaciones.
-- EMPRESA | Número operaciones |



-- 12. Mostrar el DNI de las personas junto con parejas de acciones diferentes en las que
-- el año de compra de unas acciones coincida con el año de venta de las otras.
-- DNI ACCION1|ACCION2
