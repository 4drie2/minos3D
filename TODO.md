# 📋 TODO - cub3D (42 Project)

**Projet:** cub3D - Moteur de raycasting 3D inspiré de Wolfenstein 3D
**Date:** 31 octobre 2025
**Status actuel:** ✅ Partie graphique et raycasting fonctionnels | ⏳ Parsing à implémenter

---

## 🎯 État Actuel du Projet

### ✅ CE QUI FONCTIONNE DÉJÀ

#### Raycasting & Rendu 3D
- [x] Algorithme DDA (Digital Differential Analysis) implémenté
- [x] Calcul de distance perpendiculaire (évite effet fisheye)
- [x] Calcul de hauteur de mur à l'écran
- [x] Mapping de textures XPM sur les murs
- [x] Effet de profondeur (assombrissement des murs horizontaux)
- [x] Rendu ciel et sol avec couleurs temporaires
- [x] Optimisation : image réutilisée (pas de création/destruction à chaque frame)

#### Gestion du Joueur
- [x] Déplacement avant/arrière (W/S)
- [x] Strafing gauche/droite (A/D)
- [x] Rotation gauche/droite (←/→)
- [x] Détection de collision avec les murs
- [x] Collision X et Y séparées (glissement le long des murs)

#### Gestion des Événements
- [x] Système de touches pressées/relâchées
- [x] Hook de fermeture (croix rouge + ESC)
- [x] Gestion fluide des mouvements multiples simultanés

#### Textures
- [x] Chargement de 4 textures XPM (N, S, E, W)
- [x] Libération correcte de la mémoire
- [x] Gestion d'erreur en cas d'échec de chargement
- [x] Fonction `get_texture_color()` pour récupérer les pixels

#### Infrastructure
- [x] Makefile fonctionnel avec auto-clone de libft/minilibx
- [x] Structure du projet organisée
- [x] Headers bien documentés
- [x] Fonctions avec commentaires explicatifs

---

## 🚀 CE QU'IL RESTE À FAIRE

### 📦 PRIORITÉ 1 - PARSING

#### 1.1 Parser le fichier .cub
**Fichier à modifier:** `src/parsing.c`

##### Étapes détaillées:

1. **Ouvrir et lire le fichier .cub**
   ```c
   // Vérifier l'extension .cub
   if (!ft_strnstr(filename, ".cub", ft_strlen(filename)))
       return (ft_error("Wrong file extension"));

   // Ouvrir le fichier
   int fd = open(filename, O_RDONLY);
   if (fd < 0)
       return (ft_error("Failed to open file"));
   ```

2. **Parser les éléments de texture (NO, SO, WE, EA)**
   ```c
   // Structure à ajouter dans t_data:
   typedef struct s_parse_info
   {
       char    *no_path;  // Texture Nord
       char    *so_path;  // Texture Sud
       char    *we_path;  // Texture Ouest
       char    *ea_path;  // Texture Est
       int     floor_color;   // RGB du sol (ex: 0xDC6400 pour 220,100,0)
       int     ceiling_color; // RGB du plafond
       char    **map_lines;   // Lignes brutes de la map
   }   t_parse_info;
   ```

3. **Parser les couleurs F (floor) et C (ceiling)**
   ```c
   // Format: F 220,100,0
   // Extraire R, G, B
   // Convertir en int: (R << 16) | (G << 8) | B

   int parse_color(char *line)
   {
       char **rgb = ft_split(line + 2, ','); // Séparer par virgules
       int r = ft_atoi(rgb[0]);
       int g = ft_atoi(rgb[1]);
       int b = ft_atoi(rgb[2]);

       // Vérifier range [0-255]
       if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
           return (-1);

       free_split(rgb);
       return ((r << 16) | (g << 8) | b);
   }
   ```

4. **Parser la map**
   ```c
   // La map commence après une ligne vide
   // Caractères valides: '0' (vide), '1' (mur), 'N', 'S', 'E', 'W' (spawn)

   // Étapes:
   // - Stocker toutes les lignes dans un tableau temporaire
   // - Trouver la largeur max
   // - Allouer data->map[height][width]
   // - Remplir avec 1 (mur) ou 0 (vide)
   // - Détecter la position et orientation du joueur (N/S/E/W)
   ```

5. **Valider la map**
   ```c
   // Vérifications obligatoires:
   // - Map entourée de murs (1)
   // - Un seul point de spawn (N, S, E, ou W)
   // - Pas de caractères invalides
   // - Map rectangulaire (padding avec des 1 si nécessaire)
   // - Flood fill pour vérifier que la map est fermée
   ```

##### Fonctions à créer:

```c
int     parse_file(t_data *data, char *filename);
int     parse_texture_line(t_parse_info *info, char *line);
int     parse_color_line(t_parse_info *info, char *line);
int     parse_rgb(char *str);
int     parse_map(t_data *data, char **lines, int start_idx);
int     validate_map(t_data *data);
int     is_map_closed(int **map, int width, int height);
void    find_player_spawn(t_data *data, t_parse_info *info);
void    set_player_direction(t_player *player, char orientation);
```

##### Tests à gérer:

| Fichier | Test | Résultat attendu |
|---------|------|------------------|
| `valid1.cub` | Map simple 5x5 | ✅ OK |
| `valid2.cub` | Map plus grande | ✅ OK |
| `f1_circuit.cub` | Circuit F1 | ✅ OK |
| `invalid1.cub` | Map non fermée | ❌ Error |
| `invalide2.cub` | Couleur invalide | ❌ Error |
| `invalid3.cub` | Texture manquante | ❌ Error |
| `invalid4.cub` | Plusieurs spawns | ❌ Error |
| `invalid5.cub` | Caractère invalide | ❌ Error |

---

#### 1.2 Intégrer le parsing au programme
**Fichier à modifier:** `src/main.c`, `src/texture.c`

1. **Modifier main() pour passer le fichier**
   ```c
   int main(int argc, char **argv)
   {
       t_data data;

       if (argc != 2)
           ft_error("Usage: ./cub3d <map.cub>");

       ft_memset(&data.keys, 0, sizeof(t_keys));

       if (!init_data(&data))
           ft_error("Initialization failed");

       // Parser le fichier .cub
       if (!parse_file(&data, argv[1]))
       {
           cleanup(&data);
           ft_error("Parsing failed");
       }

       // Charger les textures avec les paths du parsing
       if (!init_textures(&data))
       {
           cleanup(&data);
           ft_error("Failed to load textures");
       }

       // ... reste du code
   }
   ```

2. **Modifier init_textures() pour utiliser les paths parsés**
   ```c
   int init_textures(t_data *data)
   {
       // Remplacer les paths hardcodés par:
       // data->parse_info.no_path
       // data->parse_info.so_path
       // data->parse_info.ea_path
       // data->parse_info.we_path

       if (!load_texture(data, &data->textures[0], data->parse_info.no_path))
           return (0);
       // etc...
   }
   ```

3. **Utiliser les couleurs parsées**
   ```c
   // Dans draw_vertical_line() (raycasting.c)
   // Remplacer:
   //   0x87CEEB (ciel hardcodé)
   //   0x404040 (sol hardcodé)
   // Par:
   //   data->parse_info.ceiling_color
   //   data->parse_info.floor_color
   ```

---

### 🎨 PRIORITÉ 2 - AMÉLIORATIONS GRAPHIQUES

#### 2.1 Couleurs Floor/Ceiling dynamiques
**Fichier:** `src/raycasting.c`

```c
void draw_vertical_line(t_data *data, t_ray *ray, int x)
{
    // Remplacer les couleurs hardcodées

    // Ciel
    y = 0;
    while (y < ray->draw_start)
    {
        my_mlx_pixel_put(&data->img, x, y, data->ceiling_color);
        y++;
    }

    // ... mur ...

    // Sol
    while (y < WIN_HEIGHT)
    {
        my_mlx_pixel_put(&data->img, x, y, data->floor_color);
        y++;
    }
}
```

#### 2.2 Floor Casting (Bonus - textures au sol/plafond)
**Difficulté:** ⭐⭐⭐⭐

Permet d'avoir des textures au sol et plafond au lieu de couleurs unies.

**Algorithme:**
```c
void draw_floor_ceiling_textured(t_data *data, t_ray *ray, int x)
{
    double  ray_dir_x0 = data->player.dir_x - data->player.plane_x;
    double  ray_dir_y0 = data->player.dir_y - data->player.plane_y;
    double  ray_dir_x1 = data->player.dir_x + data->player.plane_x;
    double  ray_dir_y1 = data->player.dir_y + data->player.plane_y;

    int y = ray->draw_end + 1;
    while (y < WIN_HEIGHT)
    {
        int p = y - WIN_HEIGHT / 2;
        double pos_z = 0.5 * WIN_HEIGHT;
        double row_distance = pos_z / p;

        double floor_step_x = row_distance * (ray_dir_x1 - ray_dir_x0) / WIN_WIDTH;
        double floor_step_y = row_distance * (ray_dir_y1 - ray_dir_y0) / WIN_WIDTH;

        double floor_x = data->player.pos_x + row_distance * ray_dir_x0;
        double floor_y = data->player.pos_y + row_distance * ray_dir_y0;

        floor_x += floor_step_x * x;
        floor_y += floor_step_y * x;

        // Calculer tex_x et tex_y
        int tex_x = (int)(floor_texture.width * (floor_x - (int)floor_x)) & (floor_texture.width - 1);
        int tex_y = (int)(floor_texture.height * (floor_y - (int)floor_y)) & (floor_texture.height - 1);

        int color = get_texture_color(&floor_texture, tex_x, tex_y);
        my_mlx_pixel_put(&data->img, x, y, color);

        // Miroir pour le plafond
        my_mlx_pixel_put(&data->img, x, WIN_HEIGHT - y - 1,
                         get_texture_color(&ceiling_texture, tex_x, tex_y));
        y++;
    }
}
```

**Fichiers à modifier:**
- `include/cub3d.h` : ajouter `t_texture floor_tex` et `ceiling_tex` dans `t_data`
- `src/parsing.c` : parser `FL` et `CE` (paths de textures floor/ceiling)
- `src/texture.c` : charger ces textures
- `src/raycasting.c` : appeler la fonction de floor casting

---

### 🎮 PRIORITÉ 3 - FONCTIONNALITÉS BONUS

#### 3.1 Minimap
**Fichier:** `src/minimap.c` (à créer)

**Fonctionnalités:**
- Afficher en haut à gauche (200x200 pixels)
- Cases blanches = vide, grises = mur
- Point rouge = joueur avec direction (petit triangle)
- Transparence/bordure noire

**Implémentation:**
```c
void draw_minimap(t_data *data)
{
    int minimap_size = 200;
    int cell_size = minimap_size / 10; // Afficher 10x10 cases autour du joueur

    int start_x = (int)data->player.pos_x - 5;
    int start_y = (int)data->player.pos_y - 5;

    for (int y = 0; y < 10; y++)
    {
        for (int x = 0; x < 10; x++)
        {
            int map_x = start_x + x;
            int map_y = start_y + y;

            int color;
            if (map_x < 0 || map_x >= data->map_width ||
                map_y < 0 || map_y >= data->map_height ||
                data->map[map_y][map_x] == 1)
                color = 0x404040; // Mur
            else
                color = 0xCCCCCC; // Vide

            // Dessiner le carré
            for (int py = 0; py < cell_size; py++)
                for (int px = 0; px < cell_size; px++)
                    my_mlx_pixel_put(&data->img,
                                    x * cell_size + px + 10,
                                    y * cell_size + py + 10,
                                    color);
        }
    }

    // Dessiner le joueur (point rouge au centre)
    int player_x = 5 * cell_size + cell_size / 2 + 10;
    int player_y = 5 * cell_size + cell_size / 2 + 10;

    for (int py = -2; py <= 2; py++)
        for (int px = -2; px <= 2; px++)
            my_mlx_pixel_put(&data->img, player_x + px, player_y + py, 0xFF0000);
}
```

**Appeler dans render_frame():**
```c
int render_frame(t_data *data)
{
    update_movement(data);
    cast_rays(data);
    draw_minimap(data); // ← Ajouter ici
    mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
    return (0);
}
```

---

#### 3.2 Sprites 2D (objets dans le monde)
**Difficulté:** ⭐⭐⭐⭐⭐

Permet d'ajouter des objets 2D dans le monde 3D (lampes, ennemis, items, etc.)

**Structure:**
```c
typedef struct s_sprite
{
    double  x;          // Position X dans la map
    double  y;          // Position Y dans la map
    int     texture_id; // Quelle texture utiliser
}   t_sprite;

typedef struct s_sprite_order
{
    int     index;      // Index du sprite
    double  distance;   // Distance au joueur
}   t_sprite_order;
```

**Algorithme:**
1. Calculer la distance de chaque sprite au joueur
2. Trier les sprites du plus loin au plus proche (painter's algorithm)
3. Pour chaque sprite:
   - Transformer en coordonnées écran
   - Calculer largeur/hauteur à l'écran
   - Dessiner avec texture et transparence
   - Z-buffer pour ne pas dessiner devant les murs

**Fichiers à créer:**
- `src/sprites.c` : logique de rendu des sprites
- `src/sprites_sort.c` : tri des sprites par distance

**Références:**
- Tutoriel Lode's Raycasting: https://lodev.org/cgtutor/raycasting3.html

---

#### 3.3 Portes animées
**Difficulté:** ⭐⭐⭐

Permet d'ouvrir/fermer des portes avec la touche E.

**Implémentation:**
```c
typedef struct s_door
{
    int     map_x;
    int     map_y;
    double  open_amount; // 0.0 = fermée, 1.0 = ouverte
    int     is_opening;
    int     is_closing;
}   t_door;

// Dans la map, utiliser '2' pour une porte
// Modifier perform_dda() pour gérer les portes
// Si hit == 2 (porte):
//   - Si fermée → collision
//   - Si ouverte → continuer le rayon
//   - Si en train de s'ouvrir → collision partielle
```

**Animation:**
```c
void update_doors(t_data *data)
{
    for (int i = 0; i < data->door_count; i++)
    {
        if (data->doors[i].is_opening && data->doors[i].open_amount < 1.0)
            data->doors[i].open_amount += 0.05;
        else if (data->doors[i].is_closing && data->doors[i].open_amount > 0.0)
            data->doors[i].open_amount -= 0.05;
    }
}
```

---

#### 3.4 Souris pour la rotation
**Difficulté:** ⭐⭐

Permet de regarder avec la souris.

```c
// Dans main.c
mlx_hook(data.win, MotionNotify, PointerMotionMask, mouse_move, &data);
mlx_mouse_hide();

int mouse_move(int x, int y, t_data *data)
{
    (void)y;
    static int last_x = WIN_WIDTH / 2;

    int delta = x - last_x;

    if (delta > 0)
        rotate_right(data);
    else if (delta < 0)
        rotate_left(data);

    // Recentrer la souris
    mlx_mouse_move(data->mlx, data->win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
    last_x = WIN_WIDTH / 2;

    return (0);
}
```

---

#### 3.5 Skybox (texture de ciel)
**Difficulté:** ⭐⭐

Remplacer la couleur unie du ciel par une texture panoramique.

```c
void draw_sky(t_data *data, int x)
{
    // Calculer l'angle de vue pour cette colonne
    double camera_x = 2 * x / (double)WIN_WIDTH - 1;
    double angle = atan2(data->player.dir_y + data->player.plane_y * camera_x,
                         data->player.dir_x + data->player.plane_x * camera_x);

    // Mapper l'angle sur la largeur de la texture de skybox
    int tex_x = (int)((angle + M_PI) / (2 * M_PI) * skybox_texture.width);

    for (int y = 0; y < draw_start; y++)
    {
        // Mapper Y sur la hauteur de la texture
        int tex_y = (int)((double)y / WIN_HEIGHT * skybox_texture.height);
        int color = get_texture_color(&skybox_texture, tex_x, tex_y);
        my_mlx_pixel_put(&data->img, x, y, color);
    }
}
```

---

### 🔧 PRIORITÉ 4 - OPTIMISATIONS

#### 4.1 Multi-threading du raycasting
**Fichier:** `src/raycasting_threaded.c`

Diviser l'écran en bandes verticales et traiter chaque bande dans un thread séparé.

```c
#include <pthread.h>

typedef struct s_thread_data
{
    t_data  *data;
    int     start_x;
    int     end_x;
}   t_thread_data;

void *raycast_thread(void *arg)
{
    t_thread_data *td = (t_thread_data *)arg;
    t_ray ray;

    for (int x = td->start_x; x < td->end_x; x++)
    {
        init_ray(td->data, &ray, x);
        init_step(td->data, &ray);
        perform_dda(td->data, &ray);
        calculate_wall_distance(td->data, &ray);
        calculate_line_height(&ray);
        calculate_texture_x(td->data, &ray);
        draw_vertical_line(td->data, &ray, x);
    }

    return (NULL);
}

void cast_rays_threaded(t_data *data)
{
    pthread_t threads[4];
    t_thread_data thread_data[4];
    int band_width = WIN_WIDTH / 4;

    for (int i = 0; i < 4; i++)
    {
        thread_data[i].data = data;
        thread_data[i].start_x = i * band_width;
        thread_data[i].end_x = (i + 1) * band_width;
        pthread_create(&threads[i], NULL, raycast_thread, &thread_data[i]);
    }

    for (int i = 0; i < 4; i++)
        pthread_join(threads[i], NULL);
}
```

**Gain estimé:** +40-60% de FPS

---

#### 4.2 Texture Caching
Pré-calculer les adresses mémoire des textures.

```c
typedef struct s_texture_cache
{
    int     **pixels; // Tableau 2D de pixels
}   t_texture_cache;

// Au chargement:
void cache_texture(t_texture *tex, t_texture_cache *cache)
{
    cache->pixels = malloc(sizeof(int *) * tex->height);
    for (int y = 0; y < tex->height; y++)
    {
        cache->pixels[y] = malloc(sizeof(int) * tex->width);
        for (int x = 0; x < tex->width; x++)
            cache->pixels[y][x] = get_texture_color(tex, x, y);
    }
}

// Dans draw_vertical_line():
color = data->texture_cache[ray->tex_num].pixels[tex_y][tex_x];
```

**Gain estimé:** +10-15% de FPS

---

#### 4.3 Réduction de la résolution interne
Rendre à 640x360 puis upscaler à 1280x720.

```c
#define RENDER_WIDTH 640
#define RENDER_HEIGHT 360

// Créer une image de rendu interne
data->render_img = mlx_new_image(data->mlx, RENDER_WIDTH, RENDER_HEIGHT);

// Après le rendu, upscaler vers l'image d'affichage
mlx_put_image_to_window(data->mlx, data->win, data->render_img, 0, 0);
```

**Gain estimé:** +100-150% de FPS (qualité légèrement réduite)

---

### 🧪 PRIORITÉ 5 - TESTS & VALIDATION

#### 5.1 Tests de maps
**Créer fichier:** `tests/run_tests.sh`

```bash
#!/bin/bash

echo "🧪 Tests cub3D"

# Tests de maps valides
for map in maps/valid*.cub; do
    echo "Testing $map..."
    timeout 2s ./cub3d "$map"
    if [ $? -eq 0 ] || [ $? -eq 124 ]; then
        echo "✅ $map OK"
    else
        echo "❌ $map FAILED"
    fi
done

# Tests de maps invalides
for map in maps/invalid*.cub; do
    echo "Testing $map..."
    ./cub3d "$map" 2>&1 | grep -q "Error"
    if [ $? -eq 0 ]; then
        echo "✅ $map correctly rejected"
    else
        echo "❌ $map should have been rejected"
    fi
done
```

#### 5.2 Tests de leaks mémoire
```bash
#!/bin/bash

valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --log-file=valgrind.log \
         ./cub3d maps/valid1.cub

cat valgrind.log | grep "definitely lost"
```

#### 5.3 Vérification de la norme
```bash
norminette src include
```

---

### 📚 PRIORITÉ 6 - DOCUMENTATION

#### 6.1 README.md complet
```markdown
# cub3D

Moteur de raycasting 3D inspiré de Wolfenstein 3D.

## Compilation
make

## Utilisation
./cub3d maps/valid1.cub

## Contrôles
- W/S : Avancer/Reculer
- A/D : Strafe gauche/droite
- ← → : Rotation
- ESC : Quitter

## Format .cub
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm
F 220,100,0
C 225,30,0

111111
100001
1000N1
100001
111111
```

#### 6.2 Diagrammes d'architecture
Créer un schéma de l'architecture du code (structures, flux de données, etc.)

---

## 📊 CHECKLIST FINALE AVANT RENDU

### Fonctionnalités Obligatoires
- [ ] Parser les fichiers .cub correctement
- [ ] Gérer les textures NO, SO, WE, EA
- [ ] Gérer les couleurs F et C
- [ ] Afficher la vue 3D avec raycasting
- [ ] Déplacements fluides (W, A, S, D)
- [ ] Rotation fluide (← →)
- [ ] Détection de collision
- [ ] Fermeture propre (ESC et croix rouge)
- [ ] Gestion d'erreur pour fichiers invalides

### Qualité du Code
- [ ] Norme respectée (norminette)
- [ ] Pas de leaks mémoire (valgrind)
- [ ] Pas de segfault
- [ ] Makefile avec règles: all, clean, fclean, re
- [ ] Pas de relink inutile

### Tests
- [ ] Toutes les maps valides fonctionnent
- [ ] Toutes les maps invalides sont rejetées avec "Error\n"
- [ ] Programme stable (pas de crash aléatoire)

### Bonus (si partie obligatoire parfaite)
- [ ] Minimap
- [ ] Souris pour rotation
- [ ] Portes qui s'ouvrent/ferment
- [ ] Sprites/objets 2D
- [ ] Textures floor/ceiling

---

## 🎯 PLANNING SUGGÉRÉ

### Semaine 1 : Parsing
- Jour 1-2 : Parser textures et couleurs
- Jour 3-4 : Parser la map
- Jour 5 : Validation et gestion d'erreur
- Jour 6-7 : Tests et debug

### Semaine 2 : Intégration & Finitions
- Jour 1-2 : Intégrer parsing au programme
- Jour 3 : Couleurs dynamiques floor/ceiling
- Jour 4-5 : Tests complets et debug
- Jour 6 : Norme et leaks
- Jour 7 : Bonus (si temps)

---

## 🔗 RESSOURCES UTILES

### Documentation
- [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html) - LA référence
- [Permadi's Raycasting](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/)
- [MiniLibX Guide](https://harm-smits.github.io/42docs/libs/minilibx)

### Outils
- `valgrind` : détection de leaks
- `norminette` : vérification de la norme 42
- `gdb` : debugger

### Vidéos
- [3DSage - Raycasting Engine](https://www.youtube.com/watch?v=gYRrGTC7GtA)
- [Wolfenstein 3D Source Code Review](https://www.youtube.com/watch?v=lfEAAQcZEic)

---

## 📞 CONTACT & COLLABORATION

**Partie graphique (toi):** ✅ TERMINÉ
**Partie parsing (ton mate):** ⏳ EN COURS

**Communication :**
- Bien définir les structures communes
- S'accorder sur les valeurs de retour (0/1 ou -1/0)
- Tester l'intégration régulièrement

**Fichiers partagés critiques :**
- `include/cub3d.h` : structures communes
- `src/main.c` : point d'entrée
- `src/parsing.c` : interface entre parsing et rendering

---

## 🐛 BUGS CONNUS À CORRIGER

### Norme
- [ ] Vérifier que toutes les fonctions font < 25 lignes
- [ ] Vérifier les commentaires en français (changer en anglais si norme l'exige)
- [ ] Vérifier les déclarations de variables

### Performance
- [ ] Optimiser perform_dda() si lag sur grandes maps
- [ ] Vérifier qu'on ne recalcule pas des choses inutilement

### Robustesse
- [ ] Gérer les maps non rectangulaires (padding)
- [ ] Gérer les textures de taille non power-of-2
- [ ] Protéger contre les division par zéro

---

## 💡 NOTES IMPORTANTES

### Différences entre bonus et obligatoire
**Ne pas faire les bonus tant que la partie obligatoire n'est pas PARFAITE.**

Si un seul bug dans l'obligatoire → pas de points bonus !

### Soutenance
Préparer des réponses pour:
- Comment fonctionne l'algorithme DDA ?
- Pourquoi distance perpendiculaire et pas euclidienne ?
- Comment gérez-vous les collisions ?
- Comment mappez-vous les textures ?
- Quel est le rôle du plan caméra ?

### Astuces
- Commenter abondamment le code
- Faire des commits réguliers
- Tester sur différentes machines
- Avoir des maps de test variées

---

**DERNIÈRE MISE À JOUR:** 31 octobre 2025
**STATUS:** 🚀 Prêt pour la phase de parsing !

**BON COURAGE ! 💪**
