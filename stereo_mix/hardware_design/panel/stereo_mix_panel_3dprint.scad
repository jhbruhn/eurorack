width = 69.215;
panel_width = 70.8;
thickness = 2.2;
jack_radius = 6.1 / 2;
pot_radius = 7.1 / 2;
led_radius = 3.2 / 2;
switch_radius = 5.1 / 2;

x_offset = (128.5 - 100) / 2;
y_offset = (panel_width - width) / 2;

jacks = [[6.35, 95.25], [20.32, 95.25],
         [6.35, 85.09], [20.32, 85.09],
         [6.35, 73.74], [20.32, 73.74],
         [6.35, 63.58], [20.32, 63.58],
         [6.35, 52.15], [20.32, 52.15],
         [6.35, 41.99], [20.32, 41.99],
         [6.35, 30.32], [20.32, 30.32],
         [6.35, 20.32], [20.32, 20.32],
         [6.35,  5.08], [20.32,  5.08],
        ];
        
pots = [[39.37, 90.17], [60.69, 90.17],
        [39.37, 68.58], [60.69, 68.58],
        [39.37, 46.99], [60.69, 46.99],
        [39.37, 25.40], [60.69, 25.40]];

leds = [[50.165, 85.725],
        [50.165, 64.135],
        [50.165, 42.545],
        [50.165, 20.955]];

switches = [[50.165, 80.01],
            [50.165, 58.42],
            [50.165, 36.83],
            [50.165, 15.24]];

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
    translate([125.5, 7.5 + 11 * 5.08, -thickness / 2]) linear_extrude(height = thickness * 2)  circle(r = 3.2 / 2, $fn = 10);
    
    //bottom hole
    translate([3, 7.5, -thickness / 2]) linear_extrude(height = thickness * 2) circle(r = 3.2 / 2, $fn = 100);
    translate([3, 7.5 + 11 * 5.08, -thickness / 2]) linear_extrude(height = thickness * 2)  circle(r = 3.2 / 2, $fn = 10);
}