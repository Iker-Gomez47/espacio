--1. Obtener el número total de asignaturas.

SELECT DISTINCT count(*) FROM ASIGNATURA a;

--2. Obtener el número total de asignaturas que sean del semestre de otoño.

SELECT DISTINCT count(*) FROM ASIGNATURA a
WHERE a.SEMESTRE = 'SO';



/* 3. Obtener el mayor número de alumnos que están matriculados en una
asignatura. */

SELECT max(a.ALUMNOSMAT )
FROM ASIGNATURA a ;

/* 4. Obtener la media de alumnos matriculados en todas las asignaturas
(redondea el resultado a dos decimales). */

SELECT round(avg(a.ALUMNOSMAT ), 2)
FROM ASIGNATURA a ;

/* 5. Obtener el número total de alumnos matriculados en todas las asignaturas. */

SELECT sum(a.ALUMNOSMAT )
FROM ASIGNATURA a ;


/* 6. Obtener por cada profesor cuánta docencia tiene asignada. */

SELECT d.NIPDOC , count(*) docencia_profe
FROM DOCENCIA d 
GROUP BY d.NIPDOC
ORDER BY d.NIPDOC  ASC;

/* 7. Obtener por cada profesor cuánta docencia tiene asignada mostrando solo la
de aquellos que su docencia sea mayor de 10. Ordena el resultado por el
identificador del profesor. */

SELECT d.NIPDOC , count(*) docencia_profe
FROM DOCENCIA d 
GROUP BY d.NIPDOC
HAVING count(*) > 10
ORDER BY DOCENCIA_PROFE   ASC;

/* 8. Obtener el número total de horas de práctica y el número total de horas de
teoría de las asignaturas. */

SELECT sum(a.HORAS_PRACTICA ), sum(a.HORAS_TEORIA )
FROM ASIGNATURA a ;


/* 9. Obtener el número total de horas de práctica y el número total de horas de
teoría de las asignaturas de las cuales se imparte docencia. */

SELECT sum(a.HORAS_PRACTICA ), sum(a.HORAS_TEORIA )
FROM ASIGNATURA a , DOCENCIA d 
WHERE a.SIGLAS = d.SIGLASDOC;

/* 10. Obtener el número total de horas de prácticas y el número total de horas de
teoría que tenemos en todas las asignaturas del semestre de primavera y que
imparten su docencia profesores con un código mayor que 30. */

SELECT sum(a.HORAS_PRACTICA ), sum(a.HORAS_TEORIA )
FROM ASIGNATURA a , DOCENCIA d 
WHERE a.SIGLAS = d.SIGLASDOC AND a.SEMESTRE = 'SP' AND d.NIPDOC > 30;


/* 11. Obtener la capacidad máxima de espacio. */

SELECT max(e.CAPACIDAD )
FROM ESPACIO e; 


/* 12. Obtener la capacidad máxima de un espacio en el que se imparta docencia
de asignaturas que tengan alguna hora de prácticas. */


SELECT max(e.CAPACIDAD )
FROM ESPACIO e, DOCENCIA d , ASIGNATURA a 
WHERE e.IDESPACIO = d.ESPACIODOC AND a.SIGLAS = d.SIGLASDOC AND a.HORAS_PRACTICA > 0;


/* 13. Obtener cuántos espacios están en la primera planta. */
SELECT count(*)
FROM ESPACIO e
WHERE e.SITUACION LIKE '%Primera%';

/* 14. Obtener por cada situación cuántos espacios existen. Ordena el resultado situación. */
SELECT count(*), e.SITUACION 
FROM ESPACIO e
GROUP BY e.SITUACION
ORDER BY e.SITUACION;

/* 15. Obtener para cada día de la semana en los que hay docencia (1-5 se
corresponden con lunes-viernes) la primera y la última hora en la que se
imparte alguna clase. */

SELECT d.DIA , min(d.HORA ) primeraHora , max(d.HORA ) ultimaHora
FROM ASIGNATURA a , DOCENCIA d 
WHERE a.SIGLAS = d.SIGLASDOC 
GROUP BY d.DIA 
ORDER BY d.DIA;


/* 16. Obtener por cada semestre cuántas asignaturas tiene, la media de créditos
y el mínimo número de alumnos matriculados, siempre y cuando el semestre
no sea nulo. */

SELECT a.SEMESTRE , avg(a.CREDITOS ) mediaCreditos, min(a.ALUMNOSMAT ) minAlumnos
FROM ASIGNATURA a 
WHERE a.SEMESTRE IS NOT NULL 
GROUP BY a.SEMESTRE;


/* 17. Obtener las siglas y nombre de las asignaturas que se imparta entre 10 y 20
veces su docencia. Muestra el resultado ordenado alfabéticamente por el
nombre de asignatura. */

SELECT a.SIGLAS , a.NOMBREASIG 
FROM ASIGNATURA a , DOCENCIA d
WHERE a.SIGLAS = d.SIGLASDOC 
GROUP BY a.SIGLAS, a.NOMBREASIG  
HAVING count(*) BETWEEN 10 AND 20
ORDER BY a.NOMBREASIG;

/* 18. Obtener las horas y el número de días de la semana que hay docencia de la
asignatura 'BDa' , siempre que a esa hora se imparta la asignatura al menos 2
días por semana. Ordena el resultado por el número de días de mayor a menor
y por la hora ascendentemente. */

SELECT d.HORA , count(DISTINCT d.DIA ) AS numDias
FROM ASIGNATURA a , DOCENCIA d 
WHERE a.SIGLAS = d.SIGLASDOC AND a.SIGLAS = 'BDa'
GROUP BY d.HORA 
HAVING count(DISTINCT d.DIA ) >= 2
ORDER BY NUMDIAS DESC, d.HORA ASC;



/* 19. Obtener de la asignatura 'EDa' los pares de profesores que imparten su
docencia en el mismo tipo de clase. No pueden aparecer una fila con los
profesores 14 y 27 y otra con los profesores 27 y 14. */

SELECT d.IDOC AS profesor1 , d.IDOC AS profeso2, d.TIPOCLASE    
FROM ASIGNATURA a , DOCENCIA d 
WHERE d.SIGLASDOC = a.SIGLAS AND a.SIGLAS = 'EDa';
  

/* 20. Obtener los nombres de los espacios en mayúsculas, el edificio en el que
está y el curso más alto del que se imparte docencia en ellos. Muestra el
resultado ordenado por el nombre del espacio. */

SELECT UPPER(e.NOMBREESP) , e.EDIFICIO , max(a.CURSO)  cursoMasAlto
FROM ESPACIO e , DOCENCIA d , ASIGNATURA a 
WHERE e.IDESPACIO = d.ESPACIODOC AND a.SIGLAS = d.SIGLASDOC
GROUP BY e.NOMBREESP , e.EDIFICIO 
ORDER BY e.NOMBREESP; 


/* 21. Obtener el nombre de las asignaturas, el día en el que se imparte docencia
y cuántos profesores (distintos) las imparten considerando solo a aquellos que
no tengan una dedicación a Tiempo Completo ('TC'). Mostrar solo las
asignaturas que tengan más de 1 profesor diferente. */

SELECT a.NOMBREASIG , d.DIA , count(DISTINCT d.NIPDOC ) profDisNTC
FROM ASIGNATURA a , DOCENCIA d , PROFESOR p 
WHERE a.SIGLAS = d.SIGLASDOC AND d.NIPDOC = p.NIP AND p.DEDICACION != 'TC'
GROUP BY a.NOMBREASIG , d.DIA 
HAVING count(DISTINCT d.NIPDOC ) > 1


