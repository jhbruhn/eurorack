width = 75;
panel_width = 76.2;
thickness = 2;
jack_radius = 6.2 / 2;
pot_radius = 9.1 / 2;
led_radius = 5.1 / 2;
switch_radius = 5.1 / 2;

x_offset = (128.5 - 100) / 2;
y_offset = (panel_width - width) / 2;

jacks = [[6.35, 91.44], [6.35, 74.93], [6.35, 58.42], [6.35, 41.91], [6.35, 22.352], [6.35, 7.62],
            [19.05, 91.44], [19.05, 74.93], [19.05, 58.42], [19.05, 41.91], [19.05, 22.352], [19.05, 7.62], 
            [31.75, 22.352], [31.75, 7.62],
            [44.45, 22.352], [44.45, 7.62],
            [64.77, 22.352], [64.77, 7.62]];
pots = [[44.7675, 91.44], [44.7675, 74.93], [44.7675, 58.42], [44.7675, 41.91],
            [64.77, 91.44], [64.77, 74.93], [64.77, 58.42], [64.77, 41.91]];
leds = [];
switches = [];

difference() {
    cube(size = [128.5, panel_width, thickness]);

    for (jack = jacks)
        translate([jack[1] + x_offset, jack[0]+y_offset, -thickness / 2]) linear_extrude(height = thickness * 2) circle(r = jack_radius, $fn = 50);
    
    for (pot = pots)
        translate([pot[1] + x_offset, pot[0]+y_offset, -thickness / 2]) linear_extrude(height = thickness * 2) circle(r = pot_radius, $fn = 50);
    
    for (led = leds)
        translate([led[1] + x_offset, led[0]+y_offset, -thickness / 2]) linear_extrude(height = thickness * 2) circle(r = led_radius, $fn = 50);
    
    for (switch = switches)
        translate([switch[1] + x_offset, switch[0]+y_offset, -thickness / 2]) linear_extrude(height = thickness * 2) circle(r = switch_radius, $fn = 50);    
    // top hole
    translate([125.5, 7.5, -thickness / 2]) linear_extrude(height = thickness * 2) circle(r = 3.2 / 2, $fn = 10);
    
    //bottom hole
    translate([3, 7.5, -thickness / 2]) linear_extrude(height = thickness * 2) circle(r = 3.2 / 2, $fn = 100);
    
        // top hole
    translate([125.5, ((panel_width / 5.08) - 2) * 5.08, -thickness / 2]) linear_extrude(height = thickness * 2) circle(r = 3.2 / 2, $fn = 10);
    
    //bottom hole
    translate([3, ((panel_width / 5.08) - 2) * 5.08, -thickness / 2]) linear_extrude(height = thickness * 2) circle(r = 3.2 / 2, $fn = 100);
}