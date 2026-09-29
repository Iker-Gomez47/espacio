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


/* 11. Obtener la capacidad máxima de espacio. */


/* 12. Obtener la capacidad máxima de un espacio en el que se imparta docencia
de asignaturas que tengan alguna hora de prácticas. */


/* 13. Obtener cuántos espacios están en la primera planta. */


/* 14. Obtener por cada situación cuántos espacios existen. Ordena el resultado situación. */


/* 15. Obtener para cada día de la semana en los que hay docencia (1-5 se
corresponden con lunes-viernes) la primera y la última hora en la que se
imparte alguna clase. */


/* 16. Obtener por cada semestre cuántas asignaturas tiene, la media de créditos
y el mínimo número de alumnos matriculados, siempre y cuando el semestre
no sea nulo. */


/* 17. Obtener las siglas y nombre de las asignaturas que se imparta entre 10 y 20
veces su docencia. Muestra el resultado ordenado alfabéticamente por el
nombre de asignatura. */


/* 18. Obtener las horas y el número de días de la semana que hay docencia de la
asignatura 'BDa' , siempre que a esa hora se imparta la asignatura al menos 2
días por semana. Ordena el resultado por el número de días de mayor a menor
y por la hora ascendentemente. */


/* 19. Obtener de la asignatura 'EDa' los pares de profesores que imparten su
docencia en el mismo tipo de clase. No pueden aparecer una fila con los
profesores 14 y 27 y otra con los profesores 27 y 14. */


/* 20. Obtener los nombres de los espacios en mayúsculas, el edificio en el que
está y el curso más alto del que se imparte docencia en ellos. Muestra el
resultado ordenado por el nombre del espacio. */


/* 21. Obtener el nombre de las asignaturas, el día en el que se imparte docencia
y cuántos profesores (distintos) las imparten considerando solo a aquellos que
no tengan una dedicación a Tiempo Completo ('TC'). Mostrar solo las
asignaturas que tengan más de 1 profesor diferente. */


