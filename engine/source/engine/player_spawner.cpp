#include "stdafx.h"
#include "player_spawner.h"

Entity Player_Spawner::Spawn( LogicEngine& logic, weak<RenderEngine> rendering, weak<InputEngine> input, weak<Scene> mainScene )
{
    // LOGIC
    Entity player = Entity::New();
    auto& trans = player.add<CTransform>();
    trans.position = Vector3f(4, 4, 0);

    auto& ctrl = player.add<CControllable>();
    ctrl.name = "Player";
    ctrl.moveSpeed = 1;

    // INPUT
    if ( input ) {
        input->add_local_controller( 10, make_owner<PlayerController>( player ) );
    }

    // RENDERING
    if ( rendering && mainScene ) {
        //auto shadowtexture = rendering->get_texture( "res/textures/dev/test_shadow.png" );
        //auto rCfg2 = SpriteRenderer::Config( {
        //    /*  anchor = */{ 0, 0 },
        //    /*    size = */{ (float)shadowtexture->get_width(), (float)shadowtexture->get_height() },
        //    /* texture = */ shadowtexture,
        //    /*  entity = */ player
        //} );
        //mainScene->add_renderer<SpriteRenderer>( rCfg2 );

        //auto texture = rendering->get_texture( "res/textures/dev/test_char.png" );
        auto texture = rendering->get_texture("res/textures/player.png");
        auto rCfg = SpriteRenderer::Config( {
            /*  anchor = */{ 0, 0 },
            /*    size = */{ 0.5f, 1.0f },
            /* texture = */ texture,
            /*  entity = */ player
        } );
        auto r = mainScene->add_renderer<SpriteRenderer>( rCfg );
        SetupSubsprites(*r);
        SetupAnim0Idle(*r);
        SetupAnim1LeftWalk(*r);
        SetupAnim2RightWalk(*r);
        r->CurAnim = 1;
    }

    return player;
}

void Player_Spawner::SetupSubsprites(SpriteRenderer& r) {
  auto& idleBottom0 = r.SubSprites[0];
  idleBottom0.left = 0.25;
  idleBottom0.right = 0.375;
  idleBottom0.top = 0;
  idleBottom0.bottom = 0.25;

  auto& leftWalk0 = r.SubSprites[10];
  leftWalk0.left = 0;
  leftWalk0.right = 0.125;
  leftWalk0.top = 0.75;
  leftWalk0.bottom = 1;

  auto& leftWalk1 = r.SubSprites[11];
  leftWalk1.left = 0.125;
  leftWalk1.right = 0.25;
  leftWalk1.top = 0.75;
  leftWalk1.bottom = 1;

  auto& leftWalk2 = r.SubSprites[12];
  leftWalk2.left = 0.25;
  leftWalk2.right = 0.375;
  leftWalk2.top = 0.75;
  leftWalk2.bottom = 1;

  auto& leftWalk3 = r.SubSprites[13];
  leftWalk3.left = 0.375;
  leftWalk3.right = 0.5;
  leftWalk3.top = 0.75;
  leftWalk3.bottom = 1;

  auto& right0 = r.SubSprites[20];
  right0.left = 0;
  right0.right = 0.125;
  right0.top = 0.5;
  right0.bottom = 0.75;

  auto& right1 = r.SubSprites[21];
  right1.left = 0.125;
  right1.right = 0.25;
  right1.top = 0.5;
  right1.bottom = 0.75;

  auto& right2 = r.SubSprites[22];
  right2.left = 0.25;
  right2.right = 0.375;
  right2.top = 0.5;
  right2.bottom = 0.75;

  auto& right3 = r.SubSprites[23];
  right3.left = 0.375;
  right3.right = 0.5;
  right3.top = 0.5;
  right3.bottom = 0.75;
}

void Player_Spawner::SetupAnim1LeftWalk(SpriteRenderer& r) {
  auto& anim = r.Anims[1];

  // #0
  anim.keys[0].subSprite = 10;
  anim.keys[0].time = 250;

  // #1
  anim.keys[1].subSprite = 11;
  anim.keys[1].time = 250;

  // #2
  anim.keys[2].subSprite = 12;
  anim.keys[2].time = 250;

  // #3
  anim.keys[3].subSprite = 13;
  anim.keys[3].time = 250;
}

void Player_Spawner::SetupAnim2RightWalk(SpriteRenderer& r) {
  auto& anim = r.Anims[2];

  // #0
  anim.keys[0].subSprite = 20;
  anim.keys[0].time = 250;

  // #1
  anim.keys[1].subSprite = 21;
  anim.keys[1].time = 250;

  // #2
  anim.keys[2].subSprite = 22;
  anim.keys[2].time = 250;

  // #3
  anim.keys[3].subSprite = 23;
  anim.keys[3].time = 250;
}

void Player_Spawner::SetupAnim0Idle( SpriteRenderer& r ) {
  auto& anim = r.Anims[0];

  // #0
  anim.keys[0].subSprite = 0;
  anim.keys[0].time = 250;

  // #0
  anim.keys[1] = anim.keys[0];
  anim.keys[2] = anim.keys[0];
  anim.keys[3] = anim.keys[0];
}