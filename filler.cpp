/*
*  File:        filler.cpp
*  Description: Implementation of functions in the filler namespace.
*
*/

/*
*  Performs a flood fill using breadth first search.
*
*  PARAM:  config - FillerConfig struct to setup the fill
*  RETURN: animation object illustrating progression of flood fill algorithm
*/
animation filler::FillBFS(FillerConfig &config)
{
  // complete your implementation below
  // You should replace the following line with a
  // correct call to fill.
  int framecount = 0; // increment after processing one pixel; used for producing animation frames (step 3 above)
  
  animation anim;
  Queue<PixelPoint> os;

  // complete your implementation below
  // HINT: you will likely want to declare some kind of structure to track
  //       which pixels have already been visited
  PixelPoint seedpoint = config.seedpoint;

  os.Add(seedpoint);
  int wei = config.img.width();
  int hei = config.img.height();

  HSLAPixel *old = config.img.getPixel(seedpoint.x, seedpoint.y);
  // ColorPicker fun=*config.picker;

  HSLAPixel c = config.picker->operator()(seedpoint);
  HSLAPixel *fuck = new HSLAPixel(c);
  old->a = c.a;
  old->h = c.h;
  old->l = c.l;
  old->s = c.s;

  int dp[hei][wei]; //动态申请二维数组nxm

  for (int i = 0; i < hei; ++i)
  {
    for (int j = 0; j < wei; j++)
    {
      dp[i][j] = 0;
    }
  }

  while (!os.IsEmpty())
  {
    PixelPoint top = os.Remove();

    int x = top.x;
    int y = top.y;

    if (dp[x][y])
      continue;
    dp[x][y] = true;

    int cx[4] = {0, -1, 0, 1};
    int cy[4] = {-1, 0, 1, 0};

    PriorityNeighbours pri(top.color);
    for (int i = 0; i < 4; i++)
    {
      int newx = x + cx[i];
      int newy = y + cy[i];
      if (newx < 0 || newx >= hei || newy < 0 || newy >= wei)
        continue;

      if (dp[newx][newy] == 0)
      {
        HSLAPixel *newpix = config.img.getPixel(newx, newy);
        if (top.color.dist(*newpix) <= config.tolerance)
        {
          pri.Insert({(unsigned int)newx, (unsigned int)newy, *newpix});
        }
      }
    }

    while (!pri.IsEmpty())
    {
      auto old1 = pri.Remove();
      int x = old1.x;
      int y = old1.y;
      HSLAPixel *old = config.img.getPixel(x, y);
      // ColorPicker fun=*config.picker;

      HSLAPixel c = config.picker->operator()(old1);
      HSLAPixel *fuck = new HSLAPixel(c);
      old->a = c.a;
      old->h = c.h;
      old->l = c.l;
      old->s = c.s;

      os.Add(old1);
      framecount++;
      if (framecount == config.frameFreq)
      {
        // std::cout<<framecount<<std::endl;

        anim.addFrame(config.img);
        framecount = 0;
      }
    }
  }
  anim.addFrame(config.img);
  return anim;
}

/*
*  Performs a flood fill using depth first search.
*
*  PARAM:  config - FillerConfig struct to setup the fill
*  RETURN: animation object illustrating progression of flood fill algorithm
*/
animation filler::FillDFS(FillerConfig &config)
{
  // complete your implementation below
  // You should replace the following line with a
  // correct call to fill.
  int framecount = 0; // increment after processing one pixel; used for producing animation frames (step 3 above)
  animation anim;
  Stack<PixelPoint> os;

  // complete your implementation below
  // HINT: you will likely want to declare some kind of structure to track
  //       which pixels have already been visited
  PixelPoint seedpoint = config.seedpoint;

  os.Add(seedpoint);
  int wei = config.img.width();
  int hei = config.img.height();

  HSLAPixel *old = config.img.getPixel(seedpoint.x, seedpoint.y);
  // ColorPicker fun=*config.picker;

  HSLAPixel c = config.picker->operator()(seedpoint);
  HSLAPixel *fuck = new HSLAPixel(c);
  old->a=c.a;
  old->h=c.h;
  old->l=c.l;
  old->s=c.s;

  int dp[hei][wei]; //动态申请二维数组nxm

  for (int i = 0; i < hei; ++i)
  {
    for (int j = 0; j < wei; j++)
    {
      dp[i][j] = 0;
    }
  }

  while (!os.IsEmpty())
  {
    PixelPoint top = os.Remove();

    int x = top.x;
    int y = top.y;

    if (dp[x][y])
      continue;
    dp[x][y] = true;

    int cx[4] = {-1, 1, 0, 0};
    int cy[4] = {0, 0, -1, 1};

    PriorityNeighbours pri(top.color);
    for (int i = 0; i < 4; i++)
    {
      int newx = x + cx[i];
      int newy = y + cy[i];
      if (newx < 0 || newx >= hei || newy < 0 || newy >= wei)
        continue;

      if (dp[newx][newy] == 0)
      {
        HSLAPixel *newpix = config.img.getPixel(newx, newy);
        if (top.color.dist(*newpix) <= config.tolerance)
        {
          pri.Insert({(unsigned int)newx, (unsigned int)newy, *newpix});
        }
      }
    }
    while (!pri.IsEmpty())
    {
      auto old1 = pri.Remove();
      int x = old1.x;
      int y = old1.y;
      HSLAPixel *old = config.img.getPixel(x, y);
      // ColorPicker fun=*config.picker;

      HSLAPixel c = config.picker->operator()(old1);
      HSLAPixel *fuck = new HSLAPixel(c);
      old->a = c.a;
      old->h = c.h;
      old->l = c.l;
      old->s = c.s;

      os.Add(old1);
      framecount++;
      if (framecount == config.frameFreq)
      {
        // std::cout<<framecount<<std::endl;

        anim.addFrame(config.img);
        framecount = 0;
      }
    }
  }
  anim.addFrame(config.img);
  return anim;
}

/*
*  Run a flood fill on an image starting at the seed point
*
*  PARAM:  config - FillerConfig struct with data for flood fill of image
*  RETURN: animation object illustrating progression of flood fill algorithm
*/
template <template <typename T> class OrderingStructure>
animation filler::Fill(FillerConfig &config)
{
  /*
  * You need to implement this function!
  *
  * This is the basic description of a flood-fill algorithm: Every fill
  * algorithm requires an ordering structure, which is passed to this
  * function via its template parameter. For a breadth-first-search
  * fill, that structure is a Queue, for a depth-first-search, that
  * structure is a Stack. To begin the algorithm, you simply place the
  * given point in the ordering structure, marking it processed
  * (the way you mark it is a design decision you'll make yourself).
  * We have a choice to either change the color, if appropriate, when we
  * add the point to the OS, or when we take it off. In our test cases,
  * we have assumed that you will change the color when a point is added
  * to the structure.
  * Until the structure is empty, you do the following:
  *
  * 1.     Remove a point from the ordering structure, and then...
  *
  *        1.    add its unprocessed neighbors (up/down/left/right) whose color values are
  *              within (or equal to) tolerance distance from the center,
  *              to the ordering structure, and
  *              mark them as processed.
  *        2.    if it is an appropriate frame, send the current PNG to the
  *              animation (as described below).
  *
  * 2.     When implementing your breadth-first-search and
  *        depth-first-search fills, you will need to explore neighboring
  *        pixels (up/down/left/right) in some order.
  *
  *        While the order in which you examine neighbors does not matter
  *        for a proper fill, you must use the same order as we do for
  *        your animations to come out like ours! The order you should put
  *        neighboring pixels **ONTO** the queue or stack is based on the
  *        following priority condition:
  *        ** MINIMUM COLOR DISTANCE FROM THE CURRENT PIXEL **
  *        Ties are broken first by minimum y-coordinate, then by minimum x-coordinate.
  *        The HSLAPixel.dist() function will be useful, and you should
  *        take advantage of the functionality in your PriorityNeighbours class.
  * 
  *        If you process the neighbours in a different order, your fill may
  *        still work correctly, but your animations will be different
  *        from the grading scripts!
  *
  * 3.     For every k pixels filled, **starting at the kth pixel**, you
  *        must add a frame to the animation, where k = frameFreq.
  *
  *        For example, if frameFreq is 4, then after the 4th pixel has
  *        been filled you should add a frame to the animation, then again
  *        after the 8th pixel, etc.  You must only add frames for the
  *        number of pixels that have been filled, not the number that
  *        have been checked. So if frameFreq is set to 1, a pixel should
  *        be filled every frame.
  *
  * 4.     Finally, as you leave the function, send one last frame to the
  *        animation. This frame will be the final result of the fill, and
  *        it will be the one we test against.
  *
  */

  // int framecount = 0; // increment after processing one pixel; used for producing animation frames (step 3 above)
  animation anim;
  // OrderingStructure<PixelPoint> os;

  // // complete your implementation below
  // // HINT: you will likely want to declare some kind of structure to track
  // //       which pixels have already been visited
  // PixelPoint seedpoint= config.seedpoint;

  // os.Add(seedpoint);
  // int wei=config.img.width();
  // int hei=config.img.height();

  // int **dp=new int*[hei];//动态申请二维数组nxm

  // for(int i=0;i<hei;++i){
  //    dp[i]=new int[wei];
  //    for(int j=0;j<wei;j++)
  //    {
  //      dp[i][j]=0;
  //    }
  // }

  // while (!os.IsEmpty())
  // {
  //   PixelPoint top=os.Peek();

  //   PixelPoint center=top;
  //   os.Remove();
  //   int x=top.x;
  //   int y=top.y;
  //   dp[x][y]=true;
  //   HSLAPixel* old= config.img.getPixel(x,y);
  //   auto temp=old;
  //   config.picker();

  //   delete temp;
  //   framecount++;
  //   if (framecount==config.frameFreq)
  //   {
  //      anim.addFrame(config.img);
  //      framecount=0;
  //   }
  //    int cx[4]={0,-1,0,1};
  //    int cy[4]={-1,0,1,0};
  //   for(int i=0;i<4;i++)
  //   {
  //        int newx=x+cx[i];
  //        int newy=y+cx[i];
  //        if(newx<0||newx>=hei||newy<0||newy>=wei)
  //           continue;

  //        if(dp[newx][newy]==0)
  //        {
  //          HSLAPixel* newpix= config.img.getPixel(newx,newy);
  //          if(center.color.dist(*newpix)<config.tolerance)
  //          {
  //             os.Add({newx,newy,*newpix});
  //          }
  //        }
  //    }
  // }
  return anim;
}
