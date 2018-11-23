final int width = 500;
final int height = 300;

final int horizontal_boxes = 10;
final int vertical_boxes = 10;

final int grid_left_padding = 30;
final int grid_top_padding = 30;
final int menu_width = 200;

final int grid_width = width - menu_width - 2*grid_left_padding;
final int box_width = grid_width / horizontal_boxes;
final int box_height = (height - 2 * grid_top_padding) / vertical_boxes;

final int split_line = grid_width + grid_left_padding;

final int[] clear_button = {80, 50};
final int[] mode_buttons = {80, 50};
final String[] mode_types = {"Corner", "Messy", "Center"};
int active_mode = 1;

boolean[][] grid = new boolean[vertical_boxes][horizontal_boxes];

boolean clearing = false;

void setup() {
  size(500, 300); // should match width and height declaration
}

void draw() {
  background(200);
  // Draw Grid
  for(int y = grid_top_padding, y_index = 0; y < height - grid_top_padding; y += box_height, y_index++) {
    for(int x = grid_left_padding, x_index = 0; x < grid_width; x += box_width, x_index++) {
      if(grid[y_index][x_index]) {
        fill(100, 100, 100); 
      } else {
        fill(255, 255, 255); 
      }
      rect(x, y, box_width, box_height);
    }
  }
  
  line(split_line, 0, split_line, height);

  // Draw Menu
  // Clear Button
  if(clearing) {
    fill(255, 0, 0);
  }
  else {
    fill(255, 255, 255); 
  }
  rect(split_line + grid_left_padding, grid_top_padding, clear_button[0], clear_button[1]);
  fill(0, 0, 0);
  text("CLEAR", split_line+grid_left_padding + clear_button[0]/4, grid_top_padding + clear_button[1]/2);
  for(int i = 0; i < mode_types.length; i++) {
      if(i == active_mode) {
        fill(160, 160, 160); 
      } else {
        fill(255, 255, 255); 
      }
     rect(split_line + grid_left_padding, grid_top_padding + (i + 2) * clear_button[1], 
          mode_buttons[0], mode_buttons[1]);
     fill(0, 0, 0);
     text(mode_types[i], split_line+grid_left_padding + clear_button[0]/4, 
      grid_top_padding + (i + 2) * clear_button[1] + mode_buttons[1]/2);
  
  }
}

void mousePressed() {
  if(clearing) { // no changes can be made while currently clearing, wait for DONE signal
    text("CAN NOT CHANGE DURING CLEARING", 10, 10);
    return;
  }
  
  if(mouseX < grid_left_padding || mouseY < grid_top_padding) // near left/top border
    return;
  int x_box = (mouseX - grid_left_padding) / box_width;
  int y_box = (mouseY - grid_top_padding) / box_height;
  // inside grid
  if(x_box >= 0 && x_box < horizontal_boxes && y_box >= 0 && y_box < vertical_boxes) {
    grid[y_box][x_box] = !grid[y_box][x_box]; 
    return;
  }
  
  // clear modes
  if(mouseX > split_line + grid_left_padding && mouseX < split_line + grid_left_padding + clear_button[0]) {
    
    int normalizedY = mouseY - grid_top_padding - 2 * clear_button[1];
    int mode_box = normalizedY / mode_buttons[1];
    if(normalizedY > 0 && mode_box >= 0 && mode_box < mode_types.length) {
      active_mode = mode_box;
    }
  }

  
  
  // CLEAR
  if(mouseX > split_line + grid_left_padding && mouseX < split_line + grid_left_padding + clear_button[0]
     && mouseY > grid_top_padding && mouseY < grid_top_padding + clear_button[1]) {
    clearing = true;
    clear();
  }
  
}

void clear() {
  
}
