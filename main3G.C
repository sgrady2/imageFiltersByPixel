#include <PNMreader.h>
#include <PNMwriter.h>
#include <filters.h>

int main(int argc, char *argv[])
{
    PNMreader reader(argv[1]);

    reader.GetOutput()->Update();
    Crop crop;
    crop.SetRegion(300, 1400, 50, 400);
    crop.SetInput(reader.GetOutput());

    Transpose t;
    t.SetInput(crop.GetOutput());
    t.GetOutput()->Update();    
    
    Invert i;
    i.SetInput(t.GetOutput());
    i.GetOutput()->Update();

    //NAVY BLUE LEFT SLEEVE
    Color color(50, 1101, 0, 0, 128);
    
    LRConcat lr;
    lr.SetInput(color.GetOutput());
    lr.SetInput2(i.GetOutput());

    Color white(401, 1101, 255, 255, 255);

    Checkerboard cb;
    cb.SetInput(lr.GetOutput());
    cb.SetInput2(white.GetOutput());

    cb.GetOutput()->Update();

    PNMwriter writer;
    writer.SetInput(cb.GetOutput());
    writer.Write(argv[2]);

    CheckSum cs;
    cs.SetInput(cb.GetOutput());
    cs.OutputCheckSum("proj3G_checksum");
}
