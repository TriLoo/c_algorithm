//
// Created by smher on 17-8-16.
//

#ifndef GFILTER_GFILTER_H
#define GFILTER_GFILTER_H

class GFilter
{
public:
    GFilter() = default;
    GFilter(int r, int e, int w, int h): rad(r), eps(e), width(w), height(h){}   // constructor function to prepare the image info
    ~GFilter();

    // allocate page-locked memory and copy them to device
    // TODO : prepare Memory on page-locked memory
    void prepareMem(float *dataInI, float *dataInP);
    void createfilter();
    void boxfilter();
    void guidedfilter();

    // h_imgI : guide image on host, h_imgP : filtering image on host
    float *h_imgI, *h_imgP;
    // output
    float *Res;
    // filter on host memory
    float *filter;
    // used in guided filtering, rad : the radius of box filter
    int rad, eps;
    // width = image.col, height = image.row
    int width, height;
private:
    // d_meanI :
    float *d_imgI, *d_imgP, *d_meanI, *d_meanP, *d_tempA, *d_tempB;
    // filter on device constant memory
    float *d_filter;
    //float *d_filter, *d_eps;

    int FILTERWIDTH = 2 * rad + 1;
    int FILTERSIZE = FILTERWIDTH * FILTERWIDTH;
};

#endif //GFILTER_GFILTER_H
