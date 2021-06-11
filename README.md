# Database_lab_2

```sql
create table "Album"
(
	id serial not null
		constraint album_pk
			primary key,
	name varchar not null,
	artist varchar not null,
	genre varchar,
	number_of_tracks integer default 0 not null
);

alter table "Album" owner to grachev_alex;

create table "Music"
(
	id serial not null
		constraint music_pk
			primary key,
	name varchar not null,
	"time(min)" varchar not null,
	album_id integer not null
);

alter table "Music" owner to grachev_alex;

create table "Users"
(
	id serial not null
		constraint table_name_pk
			primary key,
	login varchar not null,
	name varchar not null,
	favorite_track_id integer
);

alter table "Users" owner to grachev_alex;


INSERT INTO "Album"("name", "artist", "genre")
 VALUES ('Eternal Atake (Deluxe) - LUV vs. The World 2', 'Lil Uzi Vert', 'hip-hop'),
        ('JACKBOYS', 'Travis Scott', 'hip-hop'),
        ('ASTROWORLD', 'Travis Scott', 'hip-hop');
        
        
INSERT INTO "Music"("name", "time(min)", "album_id")
 VALUES ('Myron', '3:44', 1),
        ('Lotus', '3:13', 1),
        ('Bean', '3:58', 1),
        ('Yessirskii', '3:39', 1),
        ('Wassup', '3:13', 1),
        ('HIGHEST IN THE ROOM', '4:05', 2),
        ('JACKBOYS', '0:46', 2),
        ('GANG GANG', '4:04', 2),
        ('GATTI', '3:01', 2),
        ('STARGAZING', '4:30', 3),
        ('CAROUSEL', '3:00', 3),
        ('SICKO MODE', '5:12', 3),
        ('R.I.P. SCREW', '3:05', 3),
        ('STOP TRUING TO BE GOD', '5:38', 3),
        ('NO BYSTANDERS', '3:38', 3);
        
        
INSERT INTO "Users"("login", "name", favorite_track_id)
VALUES ('Goodellang', 'Georgiy', 1),
       ('FixMud', 'Alesya', null),
       ('Glossyberi', 'Gadar', 10),
       ('KnightRocket', 'Leontiy', 4),
       ('Bionodo', 'Masha', null),
       ('Lulagene', 'Alyosha', 3),
       ('ShiyaSanta', 'Evgeni', 2),
       ('MrBox', 'Timur', null),
       ('NameByteIss', 'Vera', 5),
       ('ProEssence', 'Lyuba', null),
       ('HanGodzilla', 'Afanasiy', null),
       ('CandyUn', 'Kristina', 1);
```

| id | name | artist | genre | number\_of\_tracks |
| :--- | :--- | :--- | :--- | :--- |
| 1 | Eternal Atake \(Deluxe\) - LUV vs. The World 2 | Lil Uzi Vert | hip-hop | 0 |
| 2 | JACKBOYS | Travis Scott | hip-hop | 0 |
| 3 | ASTROWORLD | Travis Scott | hip-hop | 0 |


| id | name | time\(min\) | album\_id |
| :--- | :--- | :--- | :--- |
| 1 | Myron | 3:44 | 1 |
| 2 | Lotus | 3:13 | 1 |
| 3 | Bean | 3:58 | 1 |
| 4 | Yessirskii | 3:39 | 1 |
| 5 | Wassup | 3:13 | 1 |
| 6 | HIGHEST IN THE ROOM | 4:05 | 2 |
| 7 | JACKBOYS | 0:46 | 2 |
| 8 | GANG GANG | 4:04 | 2 |
| 9 | GATTI | 3:01 | 2 |
| 10 | STARGAZING | 4:30 | 3 |
| 11 | CAROUSEL | 3:00 | 3 |
| 12 | SICKO MODE | 5:12 | 3 |
| 13 | R.I.P. SCREW | 3:05 | 3 |
| 14 | STOP TRUING TO BE GOD | 5:38 | 3 |
| 15 | NO BYSTANDERS | 3:38 | 3 |


| id | login | name | favorite\_track\_id |
| :--- | :--- | :--- | :--- |
| 1 | Goodellang | Georgiy | 1 |
| 2 | FixMud | Alesya | NULL |
| 3 | Glossyberi | Gadar | 10 |
| 4 | KnightRocket | Leontiy | 4 |
| 5 | Bionodo | Masha | NULL |
| 6 | Lulagene | Alyosha | 3 |
| 7 | ShiyaSanta | Evgeni | 2 |
| 8 | MrBox | Timur | NULL |
| 9 | NameByteIss | Vera | 5 |
| 10 | ProEssence | Lyuba | NULL |
| 11 | HanGodzilla | Afanasiy | NULL |
| 12 | CandyUn | Kristina | 1 |
