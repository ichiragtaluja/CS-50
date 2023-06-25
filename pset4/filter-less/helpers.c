#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < (height); i ++)
    {
        for (int j = 0; j < (width); j ++)
        {
            float r = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0;
            int s = round(r);
            image[i][j].rgbtRed = s;
            image[i][j].rgbtGreen = s;
            image[i][j].rgbtBlue = s;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j ++)
        {
            int r = image[i][j].rgbtRed;
            int g = image[i][j].rgbtGreen;
            int b = image[i][j].rgbtBlue;

            float newred = (.393 * r + .769 * g + .189 * b) / 1.0;
            float newgreen = (.349 * r + .686 * g + .168 * b) / 1.0;
            float newblue = (.272 * r + .534 * g + .131 * b) / 1.0;

            int red = round(newred);
            int green = round(newgreen);
            int blue = round(newblue);

            if (red <= 255)
            {
                image[i][j].rgbtRed = red;
            }
            else
            {
                image[i][j].rgbtRed = 255;
            }
            if (green <= 255)
            {
                image[i][j].rgbtGreen = green;
            }
            else
            {
                image[i][j].rgbtGreen = 255;
            }
            if (blue <= 255)
            {
                image[i][j].rgbtBlue = blue;
            }
            else
            {
                image[i][j].rgbtBlue = 255;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < (width) / 2; j ++)
        {
            int r = image[i][j].rgbtRed;
            int g = image[i][j].rgbtGreen;
            int b = image[i][j].rgbtBlue;

            image[i][j].rgbtRed = image[i][(width - j - 1)].rgbtRed;
            image[i][j].rgbtGreen = image[i][(width - j - 1)].rgbtGreen;
            image[i][j].rgbtBlue = image[i][(width - j - 1)].rgbtBlue;

            image[i][(width - j - 1)].rgbtRed = r;
            image[i][(width - j - 1)].rgbtGreen = g;
            image[i][(width - j - 1)].rgbtBlue = b;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j ++)
        {
            copy[i][j].rgbtRed = image[i][j].rgbtRed;
            copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            copy[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }
    for (int k = 0; k < height; k ++)
    {
        for (int l = 0; l < width; l ++)
        {
            if ((k - 1) < 0 && (l - 1) < 0)
            {
                float Red = ((copy[k][l].rgbtRed + copy[k][l + 1].rgbtRed + copy[k + 1][l].rgbtRed
                            + copy[k + 1][l + 1].rgbtRed)) / 4.0;
                float Green = ((copy[k][l].rgbtGreen + copy[k][l + 1].rgbtGreen + copy[k + 1][l].rgbtGreen
                            + copy[k + 1][l + 1].rgbtGreen)) / 4.0;
                float Blue = ((copy[k][l].rgbtBlue + copy[k][l + 1].rgbtBlue + copy[k + 1][l].rgbtBlue
                            + copy[k + 1][l + 1].rgbtBlue)) / 4.0;

                int red = round(Red);
                int green = round(Green);
                int blue = round(Blue);


                image[k][l].rgbtRed = red;
                image[k][l].rgbtGreen = green;
                image[k][l].rgbtBlue = blue;
            }

            else if ((k + 1) > (height - 1) && (l - 1) < 0)
            {
                float RRed = ((copy[k - 1][l].rgbtRed + copy[k - 1][l + 1].rgbtRed
                             + copy[k][l].rgbtRed + copy[k][l + 1].rgbtRed)) / 4.0;
                float BBlue = ((copy[k - 1][l].rgbtBlue + copy[k - 1][l + 1].rgbtBlue
                             + copy[k][l].rgbtBlue + copy[k][l + 1].rgbtBlue)) / 4.0;
                float GGreen = ((copy[k - 1][l].rgbtGreen + copy[k - 1][l + 1].rgbtGreen
                             + copy[k][l].rgbtGreen + copy[k][l + 1].rgbtGreen)) / 4.0;

                int rred = round(RRed);
                int bblue = round(BBlue);
                int ggreen = round(GGreen);

                image[k][l].rgbtRed = rred;
                image[k][l].rgbtGreen = ggreen;
                image[k][l].rgbtBlue = bblue;
            }

            else if ((k - 1) < 0 && (l + 1) > (width - 1))
            {
                float aed = ((copy[k][l - 1].rgbtRed + copy[k][l].rgbtRed +
                            copy[k + 1][l - 1].rgbtRed + copy[k + 1][l].rgbtRed)) / 4.0;
                float areen = ((copy[k][l - 1].rgbtGreen + copy[k][l].rgbtGreen + copy[k + 1][l - 1].rgbtGreen
                              + copy[k + 1][l].rgbtGreen)) / 4.0;
                float alue = ((copy[k][l - 1].rgbtBlue + copy[k][l].rgbtBlue + copy[k + 1][l - 1].rgbtBlue
                             + copy[k + 1][l].rgbtBlue)) / 4.0;

                int r = round(aed);
                int f = round(areen);
                int p = round(alue);

                image[k][l].rgbtRed = r;
                image[k][l].rgbtGreen = f;
                image[k][l].rgbtBlue = p;
            }

            else if ((k + 1) > (height - 1) && (l + 1) > (width - 1))
            {
                float Redd = ((copy[k - 1][l - 1].rgbtRed + copy[k - 1][l].rgbtRed
                             + copy[k][l - 1].rgbtRed + copy[k][l].rgbtRed)) / 4.0;
                float Greenn = ((copy[k - 1][l - 1].rgbtGreen + copy[k - 1][l].rgbtGreen
                             + copy[k][l - 1].rgbtGreen + copy[k][l].rgbtGreen)) / 4.0;
                float Bluee = ((copy[k - 1][l - 1].rgbtBlue + copy[k - 1][l].rgbtBlue
                             + copy[k][l - 1].rgbtBlue + copy[k][l].rgbtBlue)) / 4.0;

                int rr = round(Redd);
                int gg = round(Greenn);
                int nn = round(Bluee);

                image[k][l].rgbtRed = rr;
                image[k][l].rgbtGreen = gg;
                image[k][l].rgbtBlue = nn;
            }

            else if ((k - 1) < 0 && (l - 1) >= 0 && (l + 1) < width)
            {
                float qw = ((copy[k][l - 1].rgbtRed + copy[k][l].rgbtRed + copy[k][l + 1].rgbtRed
                            + copy[k + 1][l - 1].rgbtRed + copy[k + 1][l].rgbtRed + copy[k + 1][l + 1].rgbtRed)) / 6.0;
                float ty = ((copy[k][l - 1].rgbtGreen + copy[k][l].rgbtGreen + copy[k][l + 1].rgbtGreen
                            + copy[k + 1][l - 1].rgbtGreen + copy[k + 1][l].rgbtGreen + copy[k + 1][l + 1].rgbtGreen)) / 6.0;
                float cd = ((copy[k][l - 1].rgbtBlue + copy[k][l].rgbtBlue + copy[k][l + 1].rgbtBlue
                            + copy[k + 1][l - 1].rgbtBlue + copy[k + 1][l].rgbtBlue + copy[k + 1][l + 1].rgbtBlue)) / 6.0;

                int nj = round(qw);
                int yu = round(ty);
                int tr = round(cd);

                image[k][l].rgbtRed = nj;
                image[k][l].rgbtGreen = yu;
                image[k][l].rgbtBlue = tr;
            }

            else if ((k + 1) > (height - 1) && (l - 1) >= 0 && (l + 1) < width)
            {
                float gb = ((copy[k - 1][l - 1].rgbtRed + copy[k - 1][l].rgbtRed + copy[k - 1][l + 1].rgbtRed
                            + copy[k][l - 1].rgbtRed + copy[k][l].rgbtRed + copy[k][l + 1].rgbtRed)) / 6.0;
                float za = ((copy[k - 1][l - 1].rgbtGreen + copy[k - 1][l].rgbtGreen + copy[k - 1][l + 1].rgbtGreen
                            + copy[k][l - 1].rgbtGreen + copy[k][l].rgbtGreen + copy[k][l + 1].rgbtGreen)) / 6.0;
                float re = ((copy[k - 1][l - 1].rgbtBlue + copy[k - 1][l].rgbtBlue + copy[k - 1][l + 1].rgbtBlue
                            + copy[k][l - 1].rgbtBlue + copy[k][l].rgbtBlue + copy[k][l + 1].rgbtBlue)) / 6.0;

                int plm = round(gb);
                int okn = round(za);
                int ihc = round(re);

                image[k][l].rgbtRed = plm;
                image[k][l].rgbtGreen = okn;
                image[k][l].rgbtBlue = ihc;
            }

            else if ((k - 1) >= 0 && (k + 1) < height && (l - 1) < 0)
            {
                float rew = ((copy[k - 1][l].rgbtRed + copy[k - 1][l + 1].rgbtRed + copy[k][l].rgbtRed + copy[k][l
                            + 1].rgbtRed + copy[k + 1][l].rgbtRed + copy[k + 1][l + 1].rgbtRed)) / 6.0;
                float rty = ((copy[k - 1][l].rgbtGreen + copy[k - 1][l + 1].rgbtGreen + copy[k][l].rgbtGreen
                            + copy[k][l + 1].rgbtGreen + copy[k + 1][l].rgbtGreen + copy[k + 1][l + 1].rgbtGreen)) / 6.0;
                float yui = ((copy[k - 1][l].rgbtBlue + copy[k - 1][l + 1].rgbtBlue + copy[k][l].rgbtBlue
                            + copy[k][l + 1].rgbtBlue + copy[k + 1][l].rgbtBlue + copy[k + 1][l + 1].rgbtBlue)) / 6.0;

                int lha = round(rew);
                int mbz = round(rty);
                int ehn = round(yui);

                image[k][l].rgbtRed = lha;
                image[k][l].rgbtGreen = mbz;
                image[k][l].rgbtBlue = ehn;
            }

            else if ((l + 1) > (width - 1) && (k - 1) >= 0 && (k + 1) < height)
            {
                float xx = ((copy[k - 1][l - 1].rgbtRed + copy[k - 1][l].rgbtRed + copy[k][l - 1].rgbtRed
                            + copy[k][l].rgbtRed + copy[k + 1][l - 1].rgbtRed + copy[k + 1][l].rgbtRed)) / 6.0;
                float mm = ((copy[k - 1][l - 1].rgbtGreen + copy[k - 1][l].rgbtGreen + copy[k][l - 1].rgbtGreen
                            + copy[k][l].rgbtGreen + copy[k + 1][l - 1].rgbtGreen + copy[k + 1][l].rgbtGreen)) / 6.0;
                float bb = ((copy[k - 1][l - 1].rgbtBlue + copy[k - 1][l].rgbtBlue + copy[k][l - 1].rgbtBlue
                            + copy[k][l].rgbtBlue + copy[k + 1][l - 1].rgbtBlue + copy[k + 1][l].rgbtBlue)) / 6.0;

                int nm = round(xx);
                int bn = round(mm);
                int cv = round(bb);

                image[k][l].rgbtRed = nm;
                image[k][l].rgbtGreen = bn;
                image[k][l].rgbtBlue = cv;
            }

            else
            {
                float ttt = ((copy[k - 1][l - 1].rgbtRed + copy[k - 1][l].rgbtRed + copy[k - 1][l + 1].rgbtRed
                            + copy[k][l - 1].rgbtRed + copy[k][l].rgbtRed + copy[k][l + 1].rgbtRed
                            + copy[k + 1][l - 1].rgbtRed + copy[k + 1][l].rgbtRed + copy[k + 1][l + 1].rgbtRed)) / 9.0;
                float yyy = ((copy[k - 1][l - 1].rgbtGreen + copy[k - 1][l].rgbtGreen + copy[k - 1][l + 1].rgbtGreen
                            + copy[k][l - 1].rgbtGreen + copy[k][l].rgbtGreen + copy[k][l + 1].rgbtGreen
                            + copy[k + 1][l - 1].rgbtGreen + copy[k + 1][l].rgbtGreen + copy[k + 1][l + 1].rgbtGreen)) / 9.0;
                float rrr = ((copy[k - 1][l - 1].rgbtBlue + copy[k - 1][l].rgbtBlue + copy[k - 1][l + 1].rgbtBlue
                            + copy[k][l - 1].rgbtBlue + copy[k][l].rgbtBlue + copy[k][l + 1].rgbtBlue
                            + copy[k + 1][l - 1].rgbtBlue + copy[k + 1][l].rgbtBlue + copy[k + 1][l + 1].rgbtBlue)) / 9.0;

                int lp = round(ttt);
                int yu = round(yyy);
                int ti = round(rrr);

                image[k][l].rgbtRed = lp;
                image[k][l].rgbtGreen = yu;
                image[k][l].rgbtBlue = ti;

            }
        }
    }

    return;
}
