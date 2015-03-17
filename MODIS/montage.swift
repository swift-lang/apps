type imagefile;
type landuse;
type file;

app (landuse output) landUse (imagefile input)
{
  getlanduse filename(input) stdout=filename(output);
}

app (file output, file tilelist) analyze (landuse input[], string usetype, int maxnum)
{
  analyzelanduse filename(output) filename(tilelist) usetype maxnum filename(input);
}

app (imagefile grid) mark (file tilelist, file worldmap, file convert)
{
  markmap_sh filename(tilelist) filename(grid);
}

app (imagefile output) colorize (imagefile input)
{
	colormodis filename(input) filename(output);
}

int nFiles       = toInt(arg("nfiles", "1000"));
int nSelect      = toInt(arg("nselect", "10"));
string landType  = arg("landtype", "urban");
string MODISdir  = arg("modisdir", "modis-2002/");

imagefile rawTiles[] <ext; exec="bin/modis.mapper", location=MODISdir, suffix=".modis", n=nFiles>;

landuse land[] <structured_regexp_mapper; source=rawTiles, match="(h..v..)", transform=strcat("landuse/\\1.landuse.byfreq")>;

imagefile colorImage[] <structured_regexp_mapper; source=rawTiles, match="(h..v..)", transform=strcat("colorImages/\\1.color.rgb")>;

file topSelected   <"topselected.txt">;
file selectedTiles <"selectedtiles.txt">;
imagefile gridmap <"gridmap.png">;
file world <"bin/world.rgb">;
file convert<"bin/rgb_to_png.py">;


app (imagefile mon, file o, file e) assemble (file selected, imagefile images[], string data_dir)
{
    new_assemble filename(mon) filename(selected) data_dir filenames(images) stdout=filename(o) stderr=filename(e);
}

imagefile montage<"montage.png">;
file mon_out<"montage.out">;
file mon_err<"montage.err">;
string webDir = "~/public_html/webdir";

(montage, mon_out, mon_err) = assemble (selectedTiles, colorImage, webDir);

/*


foreach raw,i in rawFiles {
    land[i] = landUse(raw,1);
    colorFiles[i] = colorize(raw);
}

(topTiles, topFiles, topColors) =
    analyze(land, landType, nSelect);

gridMap = mark(topTiles);
montage =    assemble(topFiles,colorFiles,webDir);
 */
