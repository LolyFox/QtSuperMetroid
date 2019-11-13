#include "player.h"

unsigned char Player::GetMun(){ return Mun; }

void Player::Print(QPainter * p_painter,QPixmap p_pixmap, spriteFrame p_Pix_coord[],int p_Temp){
    p_painter->drawPixmap(GetX(),GetY(),p_Pix_coord[p_Temp].width,p_Pix_coord[p_Temp].height,p_pixmap,p_Pix_coord[p_Temp].shift,p_Pix_coord[p_Temp].level,p_Pix_coord[p_Temp].width,p_Pix_coord[p_Temp].height);
}

void Player::Movement(std::vector<tilesObject> p_room)
{

    if(ota.canJump == true){
        AnimationLevel++;
        TimeJump=0;
        if(AnimationLevel > (top_jump+top_jump)*4){
            AnimationLevel=0;
            ota.canJump=false;
            SetPos(CUR_POS,(unsigned short) InitPosY);
        }else{
            TimeJump = -((AnimationLevel/4)-top_jump)*((AnimationLevel/4)-top_jump)+(top_jump*top_jump); // -(x-15)^2+15^2
            jump_count = InitPosY-TimeJump;
            // max = 15^2 = 225 ; x top = 15*
            if(pressed.D==true){
                colision = 0;
                for(unsigned int i=0; i < p_room.size(); i++){
                    if(jump_count >= p_room[i].y-41 && jump_count < p_room[i].y+16
                            && GetX() >= p_room[i].x-26 && GetX() < p_room[i].x+16){
                        if(GetX() == p_room[i].x-26 && GetY() > p_room[i].y-40){
                            // Come from north east
                            colision = 1;
                            break;
                        }
                        if(GetY()-1 < p_room[i].y-41){
                            colision = 2;
                            break;
                        }
                        colision = 3;
                        break;
                    }
                }

                if(colision == 1){
                    SetPos(CUR_POS,(unsigned short) jump_count);
                } else if(colision == 2) {
                    AnimationLevel=0;
                    ota.canJump=false;
                } else if(colision == 3){
                    AnimationLevel = (top_jump*2*speed - AnimationLevel)+4;
                } else {
                    SetPos(GetX()+1,(unsigned short) jump_count);
                }
            }
            else if(pressed.Q==true){
                colision = 0;
                for(unsigned int i=0; i < p_room.size(); i++){
                    if(jump_count >= p_room[i].y-41 && jump_count < p_room[i].y+16
                            && GetX() >= p_room[i].x-25 && GetX() <= p_room[i].x+16){
                        if(GetX() == p_room[i].x+16 && GetY() > p_room[i].y-40){
                            // Come from north east
                            colision = 1;
                            break;
                        }
                        if(GetY()-1 < p_room[i].y-41){
                            colision = 2;
                            break;
                        }
                        colision = 3;
                        break;
                    }
                }

                if(colision == 1){
                    SetPos(CUR_POS,(unsigned short) jump_count);
                } else if(colision == 2) {
                    AnimationLevel=0;
                    ota.canJump=false;
                } else if(colision == 3){
                    AnimationLevel = (top_jump*2*speed - AnimationLevel)+4;
                } else {
                    SetPos(GetX()-1,(unsigned short) jump_count);
                }
            }
            else
            {
                colision = 0;
                for(unsigned int i=0; i < p_room.size(); i++){
                    if(jump_count >= p_room[i].y-40 && jump_count < p_room[i].y+16
                            && GetX() >= p_room[i].x-25 && GetX() < p_room[i].x+16){
                        if(GetY()-1 < p_room[i].y-40){
                            colision = 1;
                            break;
                        }
                        else {
                            colision = 2;
                            break;
                        }
                    }
                }

                if(colision == 1){
                    AnimationLevel=0;
                    ota.canJump=false;
                } else if(colision == 2){
                    AnimationLevel = (2*top_jump*speed - AnimationLevel)+speed;
                } else {
                    SetPos(CUR_POS,(unsigned short) jump_count);
                }
            }
        }
    } else if(ota.fall){
        //
        colision = 0;
        for(unsigned int i=0; i < p_room.size(); i++){
            if(GetY() >= p_room[i].y-40 && GetY() < p_room[i].y+16
                    && GetX() >= p_room[i].x-26 && GetX() < p_room[i].x+16){
                if(GetX()-1 < p_room[i].x-26 || GetX()+1 >= p_room[i].x+16 ){
                    colision = 1;
                } else {
                    colision = 2;
                }
            }
        }

        if(colision == 0){
            if(pressed.D==true){
                SetPos(GetX()+1,GetY()+1);
            } else if(pressed.Q==true){
                SetPos(GetX()-1,GetY()+1);
            } else {
                SetPos(CUR_POS,GetY()+1);
            }
        }
        else if(colision == 1)
        {
            SetPos(CUR_POS,GetY()+1);
        }
        else if(colision == 2)
        {
            AnimationLevel=0;
            ota.fall= false;
        }
    } else {
        // check fall
        ota.fall = true;
        for(unsigned int i=0; i < p_room.size(); i++){
            if(GetY() >= p_room[i].y-40 && GetY() < p_room[i].y+16
                    && GetX() >= p_room[i].x-26 && GetX() < p_room[i].x+16){
                ota.fall = false;
            }
        }

        // movement left/right
        if(pressed.Q != (pressed.D) )
        {
            if(pressed.D==true)
            {
                //qInfo( "Mov = Ok" );
                AnimationLevel++;
                if(AnimationLevel == 70.0) {  AnimationLevel=0; }

                if( GetX() <= parent->width()- 30)
                {
                    SetPos(GetX()+1,CUR_POS);
                }
            }
            else if(pressed.Q==true)
            {
                AnimationLevel++;
                if(AnimationLevel >= 70) { AnimationLevel=0; }

                if( GetX() > 0)
                {
                    SetPos(GetX()-1,CUR_POS);
                }
            }
        }
    }
}

void Player::Animation(QPainter * p_painter,QPixmap p_pixmap)
{
    if(ota.fall){
        if(AnimationLevel != 80.0)
            AnimationLevel++;
          if(oldirection){
              if(AnimationLevel < 20){
                  Print(p_painter,p_pixmap,frame_JL,7);
              } else if(AnimationLevel < 40){
                    Print(p_painter,p_pixmap,frame_JL,8);
              } else if(AnimationLevel < 60){
                    Print(p_painter,p_pixmap,frame_JL,9);
              } else {
                    Print(p_painter,p_pixmap,frame_JL,10);
              }
          } else {
              if(AnimationLevel < 20){
                  Print(p_painter,p_pixmap,frame_JR,7);
              } else if(AnimationLevel < 40){
                    Print(p_painter,p_pixmap,frame_JR,8);
              } else if(AnimationLevel < 60){
                    Print(p_painter,p_pixmap,frame_JR,9);
              } else {
                    Print(p_painter,p_pixmap,frame_JR,10);
              }
          }
      } else if(ota.canJump){
        if(pressed.right){
            if(pressed.up){
                Print(p_painter,p_pixmap,frameOTA_R,Up_Dir);
            } else if(pressed.down){
                Print(p_painter,p_pixmap,frameOTA_R,Down_Dir);
            } else {
                Print(p_painter,p_pixmap,frameOTA_R,Local_Dir);
            }
        } else if(pressed.left){
            if(pressed.up){
                Print(p_painter,p_pixmap,frameOTA_L,Up_Dir);
            } else if(pressed.down){
                Print(p_painter,p_pixmap,frameOTA_L,Down_Dir);
            } else {
                Print(p_painter,p_pixmap,frameOTA_L,Local_Dir);
            }
        } else if(pressed.up){
            if(oldirection){
                Print(p_painter,p_pixmap,frameOTA_L,Up);
            } else {
                Print(p_painter,p_pixmap,frameOTA_R,Up);
            }
        } else if(pressed.down){
            if(oldirection){
                Print(p_painter,p_pixmap,frameOTA_L,Down);
            } else {
                Print(p_painter,p_pixmap,frameOTA_R,Down);
            }
        } else {
            if(ota.maxJump){
                if(oldirection){
                    Print(p_painter,p_pixmap,frame_JL,11);
                }else{
                    Print(p_painter,p_pixmap,frame_JR,11);
                }
            } else {
                if(oldirection){
                    Print(p_painter,p_pixmap,frame_JL,2);
                } else {
                    Print(p_painter,p_pixmap,frame_JR,2);
                }
            }
        }
    } else if(pressed.jump || pressed.Q || pressed.D){
      if(pressed.jump){
          if(oldirection){
              Print(p_painter,p_pixmap,frame_JL,0);
          } else {
              Print(p_painter,p_pixmap,frame_JR,0);
          }
      } else if(pressed.D){
          if (pressed.up){
              // run canon up
              Print(p_painter,p_pixmap,frame_DU,AnimationLevel/7);
          } else if(pressed.down){
              // run canon down
              Print(p_painter,p_pixmap,frame_DD,AnimationLevel/7);
          } else if(pressed.right){
              // run canon
              Print(p_painter,p_pixmap,frame_DR,AnimationLevel/7);
          } else {
              // normal run
              Print(p_painter,p_pixmap,frame_D,AnimationLevel/7);
          }
      } else if(pressed.Q){
          if (pressed.up){
              // run canon up
              Print(p_painter,p_pixmap,frame_QU,AnimationLevel/7);
          } else if(pressed.down){
              // run canon down
              Print(p_painter,p_pixmap,frame_QD,AnimationLevel/7);
          } else if(pressed.left){
              // run canon
              Print(p_painter,p_pixmap,frame_QL,AnimationLevel/7);
          } else {
              // normal run
              Print(p_painter,p_pixmap,frame_Q,AnimationLevel/7);
          }
      }
  } else {
      if(pressed.S){ // comment
          if(pressed.right){
              if (pressed.up){
                  // dir up right
                  Print(p_painter,p_pixmap,frame_S_R,4);
              } else {
                  Print(p_painter,p_pixmap,frame_S_R,2);
              }
          } else if (pressed.left){
              if (pressed.up){
                  // dir up left
                  Print(p_painter,p_pixmap,frame_S_L,4);
              } else {
                  // dir left
                  Print(p_painter,p_pixmap,frame_S_L,2);
              }
          } else if (pressed.up){
              if(oldirection){
                  Print(p_painter,p_pixmap,frame_S_L,3);
              }else{
                  Print(p_painter,p_pixmap,frame_S_R,3);
              }

          } else {
              // stay current state // breath
              /* -------------------------- breath */
              AnimationLevel++;
              if(oldirection){
                  if(AnimationLevel < 20){
                     Print(p_painter,p_pixmap,frame_S_L,0);
                  }else if(AnimationLevel < 40){
                    Print(p_painter,p_pixmap,frame_S_L,1);
                  }else if(AnimationLevel < 60){
                      Print(p_painter,p_pixmap,frame_S_L,2);
                  } else{
                      Print(p_painter,p_pixmap,frame_S_L,2);
                      AnimationLevel=0;
                  }
              } else {
                  if(AnimationLevel < 20){
                     Print(p_painter,p_pixmap,frame_S_R,0);
                  }else if(AnimationLevel < 40){
                    Print(p_painter,p_pixmap,frame_S_R,1);
                  }else if(AnimationLevel < 60){
                      Print(p_painter,p_pixmap,frame_S_R,2);
                  } else{
                      Print(p_painter,p_pixmap,frame_S_R,2);
                      AnimationLevel=0;
                  }
              }
              /* -------------------------- end breath */
          }
      } else { // comment
          if(pressed.right){
              if (pressed.up){
                  // dir up right
                  Print(p_painter,p_pixmap,frame_R,Up_Dir);
              }else if(pressed.down){
                  // dir down right
                  Print(p_painter,p_pixmap,frame_R,Down_Dir);
              } else {
                  // dir  breath right
                  Print(p_painter,p_pixmap,frame_R,Local_Dir);
              }
          } else if (pressed.left){
              if (pressed.up){
                  // dir up left
                  Print(p_painter,p_pixmap,frame_L,Up_Dir);
              }else if(pressed.down){
                  // dir down left
                  Print(p_painter,p_pixmap,frame_L,Down_Dir);
              } else {
                  // dir left
                  Print(p_painter,p_pixmap,frame_L,Local_Dir);
              }
          } else if (pressed.up){
              // dir_up
              if(oldirection){
                  Print(p_painter,p_pixmap,frame_L,Up);
              } else {
                  Print(p_painter,p_pixmap,frame_R,Up);
              }
          } else {
              // stay current state
              /* -------------------------- breath */
              AnimationLevel++;
              if(oldirection){
                  if(AnimationLevel < 20){
                      Print(p_painter,p_pixmap,frame_L,Other);
                  }else if(AnimationLevel < 40){
                     Print(p_painter,p_pixmap,frame_L,Other+1);
                  }else if(AnimationLevel < 60){
                      Print(p_painter,p_pixmap,frame_L,Other+2);
                  } else{
                      Print(p_painter,p_pixmap,frame_L,Other+2);
                      AnimationLevel=0;
                  }
              } else {
                  if(AnimationLevel < 20){
                      Print(p_painter,p_pixmap,frame_R,Other);
                  }else if(AnimationLevel < 40){
                     Print(p_painter,p_pixmap,frame_R,Other+1);
                  }else if(AnimationLevel < 60){
                     Print(p_painter,p_pixmap,frame_R,Other+2);
                  } else{
                     Print(p_painter,p_pixmap,frame_R,Other+2);
                     AnimationLevel=0;
                  }
              }
              /* -------------------------- end breath */
          }
      }
    }
}

void Player::Key_event(QKeyEvent * event)
{
    if(event->key() == Qt::Key_F ){
        if(ota.fall== false){
            ota.fall = true;
            AnimationLevel = 0;
        }
    }

    if(event->count() == 2)
    {
        if(event->key() == Qt::Key_Right )
        {
            pressed.right=true;
            oldirection = false;
            if(event->key() == Qt::Key_Up){
                pressed.up=true;
            } else if(event->key() == Qt::Key_Down){
                pressed.down=true;
            }
        }else if(event->key() == Qt::Key_Left){
            pressed.left=true;
            oldirection = true;
            if(event->key() == Qt::Key_Up){
                pressed.up=true;
            } else if(event->key() == Qt::Key_Down){
                pressed.down=true;
            }
        }
    }
    else if(event->key() == Qt::Key_D )
    {
        if(pressed.D == false)
        {
            pressed.D=true;
            oldirection = false;
            if (!ota.canJump && !ota.fall)
                AnimationLevel=0;
        }
    }
    else if(event->key() == Qt::Key_Q)
    {
        if(pressed.Q == false)
        {
            pressed.Q=true;
            oldirection = true;
            if (!ota.canJump && !ota.fall)
                AnimationLevel=0;
        }
    }
    else if(event->key() == Qt::Key_S)
    {
        if(pressed.S == false)
        {
            pressed.S = true;
            if (!ota.canJump && !ota.fall)
                AnimationLevel=0;

        }
    }
    else if(event->key() == Qt::Key_Right){
        if(pressed.right == false)
        {
            pressed.right = true;
            oldirection = false;
        }
    }
    else if(event->key() == Qt::Key_Left){
        if(pressed.left == false)
        {
            pressed.left = true;
            oldirection = true;
        }
    }
    else if(event->key() == Qt::Key_Up){
        if(pressed.up == false)
        {
            pressed.up = true;
        }
    }
    else if(event->key() == Qt::Key_Down){
        if(pressed.down == false)
        {
            pressed.down = true;
        }
    }
    else if(event->key() == Qt::Key_Shift)
    {
        if(pressed.jump == false && ota.fall == false && ota.canJump == false)
        {
            pressed.jump=true;
            InitPosY = GetY();
            timerJump->start(100);
            AnimationLevel=0;
        }
    }
    else if(event->key() == Qt::Key_Space)
    {
        //TODO : fire gun
    }
}

void Player::loading_jump()
{
    if(pressed.jump == true && ota.canJump == false){
        load_count++;
        if(load_count == 15.0){
            ota.canJump = true;
            top_jump=(load_count/3)+10;
            load_count=0;
            ota.maxJump=true;
            timerJump->stop();
        }
    } else if(ota.canJump == false){
        ota.canJump=true;
        top_jump=(load_count/3)+10;
        ota.maxJump=false;
        load_count=0;
        timerJump->stop();
    }
    AnimationLevel=0;
}

