import os
import random
from PIL import Image, ImageDraw

# Configuration
TEXTURE_SIZE = 256
OUTPUT_DIR = "textures"
COLORS = {
    "stone_light": [(140, 130, 120), (150, 140, 130), (160, 150, 140)],
    "stone_dark": [(80, 70, 60), (90, 80, 70), (100, 90, 80)],
    "mortar": (40, 35, 30),
    "ivy_light": (60, 160, 60),
    "ivy_dark": (30, 100, 30),
    "frieze_bg": (220, 210, 190),
    "frieze_red": (160, 40, 40),
    "frieze_blue": (40, 60, 140),
    "frieze_gold": (180, 140, 40)
}

def ensure_dir():
    if not os.path.exists(OUTPUT_DIR):
        os.makedirs(OUTPUT_DIR)

def generate_brick_wall(draw, width, height, dark_mode=False):
    # Fond (Mortier)
    draw.rectangle([(0, 0), (width, height)], fill=COLORS["mortar"])
    
    rows = 16
    cols = 8
    brick_h = height // rows
    brick_w = width // cols
    
    stone_palette = COLORS["stone_dark"] if dark_mode else COLORS["stone_light"]

    for r in range(rows):
        offset = (brick_w // 2) if r % 2 == 0 else 0
        for c in range(-1, cols + 1):
            x = c * brick_w + offset
            y = r * brick_h
            
            # Variation aléatoire de la couleur de la brique
            color = random.choice(stone_palette)
            
            # Dessin de la brique avec une marge pour le mortier
            draw.rectangle(
                [(x + 2, y + 2), (x + brick_w - 2, y + brick_h - 2)],
                fill=color
            )
            
            # Ajout de bruit/texture sur la brique
            for _ in range(20):
                nx = x + random.randint(2, brick_w - 3)
                ny = y + random.randint(2, brick_h - 3)
                shade = (max(0, color[0]-20), max(0, color[1]-20), max(0, color[2]-20))
                draw.point((nx, ny), fill=shade)

def draw_greek_frieze(draw, y_pos, color_pattern):
    # Fond de la frise
    h = 32
    draw.rectangle([(0, y_pos), (TEXTURE_SIZE, y_pos + h)], fill=COLORS["frieze_bg"])
    
    # Motif Grec (Meander simple)
    # 0 = vide, 1 = couleur
    pattern = [
        [1,1,1,1,1,1,1,0],
        [1,0,0,0,0,0,1,0],
        [1,0,1,1,1,0,1,0],
        [1,0,1,0,1,0,1,0],
        [1,0,1,0,0,0,1,0],
        [1,0,1,1,1,1,1,0],
        [0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0]
    ]
    
    scale = 4
    pat_w = 8 * scale
    
    for x_offset in range(0, TEXTURE_SIZE, pat_w):
        for r, row in enumerate(pattern):
            for c, val in enumerate(row):
                if val:
                    x = x_offset + c * scale
                    y = y_pos + 4 + r * scale
                    draw.rectangle([(x, y), (x + scale - 1, y + scale - 1)], fill=color_pattern)
    
    # Bordures de la frise
    draw.rectangle([(0, y_pos), (TEXTURE_SIZE, y_pos+2)], fill=color_pattern)
    draw.rectangle([(0, y_pos+h-2), (TEXTURE_SIZE, y_pos+h)], fill=color_pattern)

def draw_ivy(draw, density=10):
    # Lierre tombant du haut
    num_vines = density
    for _ in range(num_vines):
        x = random.randint(0, TEXTURE_SIZE)
        y = 0
        length = random.randint(50, 200)
        
        # Marche aléatoire vers le bas
        for i in range(length):
            x += random.randint(-2, 2)
            y += random.randint(1, 3)
            
            # Dessin de la feuille (cluster de pixels)
            color = random.choice([COLORS["ivy_light"], COLORS["ivy_dark"]])
            draw.rectangle([(x, y), (x+3, y+3)], fill=color)
            
            if x < 0: x += TEXTURE_SIZE
            if x >= TEXTURE_SIZE: x -= TEXTURE_SIZE

def save_as_xpm(img, filename):
    # Réduire les couleurs pour optimiser la taille du XPM (quantization)
    img = img.quantize(colors=64)
    width, height = img.size
    
    # Mapping couleurs -> caractères
    # XPM utilise des char ASCII pour coder les pixels
    palette = img.getpalette()
    # getpalette retourne une liste plate [r, g, b, r, g, b...], on doit grouper
    colors = []
    if palette:
        for i in range(0, len(palette), 3):
            colors.append((palette[i], palette[i+1], palette[i+2]))
    
    # Générer les codes caractères (ex: "aa", "ab", etc.)
    # On utilise 2 caractères par pixel pour avoir assez de combinaisons
    chars_code = []
    chars_set = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
    for c1 in chars_set:
        for c2 in chars_set:
            chars_code.append(f"{c1}{c2}")
    
    # Header XPM
    xpm_content = []
    xpm_content.append("/* XPM */")
    xpm_content.append(f"static char *{filename.split('.')[0]}[] = {{")
    
    # Info ligne: width height num_colors chars_per_pixel
    num_colors = len(img.getcolors())
    # Attention: img.getcolors() peut retourner None si > 256 couleurs, 
    # mais on a quantize à 64.
    # Pour être sûr, on prend la taille de la palette utilisée par quantize
    # Par sécurité on recompte les index uniques utilisés
    data_pixels = list(img.getdata())
    unique_indices = set(data_pixels)
    real_num_colors = len(unique_indices)
    
    xpm_content.append(f"\"{width} {height} {real_num_colors} 2\",")
    
    # Palette definition
    # Format: "code c #RRGGBB"
    index_to_char = {}
    sorted_indices = sorted(list(unique_indices))
    
    for i, idx in enumerate(sorted_indices):
        code = chars_code[i]
        index_to_char[idx] = code
        r, g, b = colors[idx]
        hex_col = f"#{r:02X}{g:02X}{b:02X}"
        xpm_content.append(f"\"{code} c {hex_col}\",")
    
    # Pixel data
    for y in range(height):
        row_str = ""
        for x in range(width):
            pixel_idx = img.getpixel((x, y))
            row_str += index_to_char[pixel_idx]
        
        line_end = "," if y < height - 1 else ""
        xpm_content.append(f"\"{row_str}\"{line_end}")
    
    xpm_content.append("};")
    
    # Écriture fichier
    full_path = os.path.join(OUTPUT_DIR, filename)
    with open(full_path, "w") as f:
        f.write("\n".join(xpm_content))
    print(f"Generated: {full_path}")

def main():
    ensure_dir()
    
    # --- NORTH: Standard Brick + Red Frieze + Light Ivy ---
    img_n = Image.new("RGB", (TEXTURE_SIZE, TEXTURE_SIZE))
    draw_n = ImageDraw.Draw(img_n)
    generate_brick_wall(draw_n, TEXTURE_SIZE, TEXTURE_SIZE, dark_mode=False)
    draw_greek_frieze(draw_n, 100, COLORS["frieze_red"])
    draw_ivy(draw_n, density=8)
    save_as_xpm(img_n, "north.xpm")

    # --- SOUTH: Darker Brick + Blue Frieze + Heavy Ivy ---
    img_s = Image.new("RGB", (TEXTURE_SIZE, TEXTURE_SIZE))
    draw_s = ImageDraw.Draw(img_s)
    generate_brick_wall(draw_s, TEXTURE_SIZE, TEXTURE_SIZE, dark_mode=True)
    draw_greek_frieze(draw_s, 100, COLORS["frieze_blue"])
    draw_ivy(draw_s, density=15)
    save_as_xpm(img_s, "south.xpm")

    # --- EAST: Standard Brick + Gold Frieze + No Ivy ---
    img_e = Image.new("RGB", (TEXTURE_SIZE, TEXTURE_SIZE))
    draw_e = ImageDraw.Draw(img_e)
    generate_brick_wall(draw_e, TEXTURE_SIZE, TEXTURE_SIZE, dark_mode=False)
    draw_greek_frieze(draw_e, 100, COLORS["frieze_gold"])
    # Pas de lierre
    save_as_xpm(img_e, "east.xpm")

    # --- WEST: Dark Brick + Gold Frieze + Medium Ivy ---
    img_w = Image.new("RGB", (TEXTURE_SIZE, TEXTURE_SIZE))
    draw_w = ImageDraw.Draw(img_w)
    generate_brick_wall(draw_w, TEXTURE_SIZE, TEXTURE_SIZE, dark_mode=True)
    draw_greek_frieze(draw_w, 100, COLORS["frieze_gold"])
    draw_ivy(draw_w, density=5)
    save_as_xpm(img_w, "west.xpm")

if __name__ == "__main__":
    main()
