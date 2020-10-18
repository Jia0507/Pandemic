#include <iostream>
#include <bangtal>


using namespace std;
using namespace bangtal;

//Item 클래스 선언

class Item : public Object
{
public:
	static ObjectPtr create(const string& image, ScenePtr scene = nullptr, int x = 0, int y = 0, bool shown = true) {

		auto object = ObjectPtr(new Item(image, scene, x, y, shown));
		Object::add(object);
		return object;
	}

protected:
	Item(const string& image, ScenePtr scene, int x, int y, bool shown) : Object(image, scene, x, y, shown) {}
public:
	virtual bool onMouse(int x, int y, MouseAction action) {
		if (!Object::onMouse(x, y, action)) {
			pick();
		}
		return true;
	}

};

int main()
{

	auto main = Scene::create("Pandemic", "images/배경.png");
	auto scene1 = Scene::create("Room1", "images/방.png");
	auto scene_message = Scene::create("? from ?", "images/쪽지.png");
	auto scene2 = Scene::create("Room2", "images/방.png");
	auto scene2_1 = Scene::create("Lab", "images/방.png");
	auto scene2_1_monitor = Scene::create("?", "images/화면.png");
	auto scene2_1_memo = Scene::create("알수 없는 메모", "images/scene_memo.png");
	auto scene2_2 = Scene::create("?", "images/비밀의방.png");
	auto scene_final = Scene::create("", "images/방.png");
	auto scene3 = Scene::create("Room3", "images/방.png");
	auto scene3_memo = Scene::create("알수 없는 메모", "images/another_memo.png");
	auto scene_basement = Scene::create("Basement", "images/basement.png");
	auto scene_end = Scene::create("?의 경고", "images/end_page.png");
	auto scene4 = Scene::create("", "images/방.png");
	auto the_end = Scene::create("", "images/final_page.png");
	auto start_button = Object::create("images/start.png", main, 50, 100);
	auto end_button = Object::create("images/end.png", main, 50, 10);

	start_button->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene1->enter();
		return true;
		});

	end_button->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		endGame();
		return true;
		});

	//Scene1 

	auto key_hanger = Object::create("images/열쇠걸이.png", scene1, 300, 500);
	auto key_to_scene2 = Item::create("images/열쇠.png", scene1, 320, 470);
	auto blue_key = Item::create("images/푸른열쇠.png", scene1, 350, 475);
	auto orange_key = Item::create("images/주황열쇠.png", scene1, 380, 480);
	auto green_key = Item::create("images/초록열쇠.png", scene1, 410, 485);

	auto door1 = Object::create("images/문-오른쪽-닫힘.png", scene1, 900, 275);

	auto door1_locked = true;
	auto door1_closed = true;

	auto message = Object::create("images/작은쪽지.png", scene1, 500, 100);

	auto back1 = Object::create("images/back.png", scene_message, 0, 620);

	message->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene_message->enter();
		return true;
		});

	back1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene1->enter();
		return true;
		});


	door1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (door1_locked) {

			showMessage("문이 잠겨있다.");

			if (key_to_scene2->isHanded()) {

				door1_locked = false;
				showMessage("철커덕.");
			}
		}

		else if (door1_locked == false && door1_closed == true) {

			door1->setImage("images/문-오른쪽-열림.png");
			showMessage("문이 열렸다.");
			door1_closed = false;

		}

		else if (door1_locked == false && door1_closed == false) {

			scene2->enter();
		}

		return true;
		});


	//Scene2

	auto door2 = Object::create("images/문-왼쪽-열림.png", scene2, 320, 270);

	door2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene1->enter();
		return true;
		});


	auto door3 = Object::create("images/문-오른쪽-닫힘.png", scene2, 700, 305);
	auto door4 = Object::create("images/문-오른쪽-닫힘.png", scene2, 900, 275);
	auto door5 = Object::create("images/문-오른쪽-닫힘.png", scene2, 1100, 242);

	auto door3_locked = true;
	auto door3_closed = true;

	auto door4_locked = true;
	auto door4_closed = true;

	auto door5_closed = true;

	door3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (door3_locked) {

			showMessage("문이 잠겨있다.");

			if (blue_key->isHanded()) {

				door3_locked = false;
				showMessage("철커덕.");
			}
		}

		else if (door3_locked == false && door3_closed == true) {

			door3->setImage("images/문-오른쪽-열림.png");
			showMessage("문이 열렸다.");
			door3_closed = false;

		}

		else if (door3_locked == false && door3_closed == false) {

			scene2_1->enter();
		}

		return true;
		});

	door4->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (door4_locked) {

			showMessage("문이 잠겨있다.");

			if (green_key->isHanded()) {

				door4_locked = false;
				showMessage("철커덕.");
			}
		}

		else if (door4_locked == false && door4_closed == true) {

			door4->setImage("images/문-오른쪽-열림.png");
			showMessage("문이 열렸다.");
			door4_closed = false;

		}

		else if (door4_locked == false && door4_closed == false) {

			scene2_2->enter();
		}

		return true;
		});


	door5->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (door5_closed) {

			showMessage("문이 열렸다.");
			door5_closed = false;
			door5->setImage("images/문-오른쪽-열림.png");
		}
		else if (door5_closed == false) {

			scene3->enter();
		}


		return true;
		});

	auto stair = Object::create("images/stair.png", scene2, 480, 10);
	stair->setScale(1.5f);
	stair->hide();

	stair->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene_basement->enter();
		showMessage("쿠궁--");
		return true;
		});


	//Scene 2_1

	auto door2_2 = Object::create("images/문-왼쪽-열림.png", scene2_1, 320, 270);
	auto switch_ = Object::create("images/스위치.png", scene2_1, 280, 420);
	switch_->setScale(1.5f);

	scene2_1->setLight(0.5f);

	auto set_lighted = false;

	switch_->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (set_lighted == false) {

			set_lighted = true;
			scene2_1->setLight(1.0f);
		}

		else {
			scene2_1->setLight(0.2f);
			set_lighted = false;
		}
		return true;
		});


	door2_2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene2->enter();
		return true;
		});

	auto lighted_ = false;
	auto memo = Object::create("images/memo.png", scene2_1, 300, 100);
	auto back_memo = Object::create("images/back.png", scene2_1_memo, 0, 620);

	memo->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene2_1_memo->enter();
		return true;
		});

	back_memo->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene2_1->enter();
		return true;
		});


	auto desk = Object::create("images/desk.png", scene2_1, 600, 220);
	auto monitor = Object::create("images/monitor.png", scene2_1, 800, 420);

	desk->setScale(0.8f);
	auto shelf = Object::create("images/선반.png", scene2_1, 950, 180);
	shelf->setScale(0.8f);

	auto light = Object::create("images/light.png", scene2_2, 210, 520);
	light->setScale(0.6f);
	light->hide();

	monitor->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		lighted_ = true;
		scene2_1_monitor->enter();

		if (lighted_) {
			light->show();

		}
		return true;

		});

	auto back2 = Object::create("images/back2.png", scene2_1_monitor, 0, 620);

	back2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene2_1->enter();
		return true;
		});



	auto drug_A = Item::create("images/drug_A.png", scene2_1, 1000, 480);
	auto drug_Z = Item::create("images/drug_Z.png", scene2_1, 1080, 470);
	auto drug_Y = Item::create("images/drug_Y.png", scene2_1, 1160, 460);
	auto drug_K = Item::create("images/drug_K.png", scene2_1, 1000, 375);
	auto drug_T = Item::create("images/drug_T.png", scene2_1, 1080, 360);
	auto drug_I = Item::create("images/drug_I.png", scene2_1, 1160, 345);
	auto drug_G = Item::create("images/drug_G.png", scene2_1, 1000, 275);
	auto drug_X = Item::create("images/drug_X.png", scene2_1, 1080, 260);
	auto drug_E = Item::create("images/drug_E.png", scene2_1, 1160, 245);

	drug_A->setScale(0.5f);
	drug_Z->setScale(0.5f);
	drug_Y->setScale(0.5f);
	drug_K->setScale(0.5f);
	drug_T->setScale(0.5f);
	drug_I->setScale(0.5f);
	drug_G->setScale(0.5f);
	drug_X->setScale(0.5f);
	drug_E->setScale(0.5f);

	auto drug_unknown = Item::create("images/drug_unknown.png", scene2_1, 0, 0, false);
	drug_unknown->defineCombination(drug_X, drug_Y);
	if (drug_X->onCombine() && drug_Y->onCombine()) {
		drug_unknown->pick();
	}

	auto drug_missed = Item::create("images/drug_missed.png", scene2_1, 0, 0, false);
	drug_missed->defineCombination(drug_A, drug_K);
	if (drug_A->onCombine() && drug_K->onCombine()) {
		drug_missed->pick();
	}



	//Scene2_2


	auto door2_3 = Object::create("images/문-왼쪽-열림.png", scene2_2, 320, 270);

	door2_3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene2->enter();
		return true;
		});

	auto hidden_door = Object::create("images/또다른문.png", scene2_2, 900, 265);
	hidden_door->hide();

	hidden_door->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene_final->enter();
		return true;
		});

	//Scene3

	auto door2_4 = Object::create("images/문-왼쪽-열림.png", scene3, 90, 225);

	door2_4->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene2->enter();
		return true;
		});

	auto lab_desk = Object::create("images/lab_desk.png", scene3, 210, 130);
	auto worktable = Object::create("images/worktable.png", scene3, 700, 200);
	auto syringe = Item::create("images/syringe.png", scene3, 230, 360);

	auto syringe_fulled_1 = Object::create("images/syringe_fulled.png", scene3, 0, 0, false);
	auto syringe_fulled_2 = Object::create("images/syringe_fulled.png", scene3, 0, 0, false);

	syringe_fulled_1 ->defineCombination(syringe, drug_unknown);
	if (syringe->onCombine() && drug_unknown->onCombine()) {
		syringe_fulled_1->pick();
	}
	syringe_fulled_2 ->defineCombination(syringe, drug_missed);
	if (syringe->onCombine() && drug_missed->onCombine()) {
		syringe_fulled_2 -> pick();
	}

	auto dish = Item::create("images/dish.png", scene3, 760, 280);
	dish->setScale(0.8f);

	auto another_memo = Object::create("images/memo.png", scene3, 760, 280);
	another_memo->setScale(0.8f);
	auto back3 = Object::create("images/back.png", scene3_memo, 0, 620);

	auto memo_check = false;

	another_memo->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene3_memo->enter();
		return true;
		});

	auto dish_drop = false;

	back3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene3->enter();
		memo_check = true;
		if (memo_check == true && dish->isHanded()) {
			showMessage("쿠궁--!");
			stair->show();
		}
		return true;
		});

	auto door6 = Object::create("images/문-오른쪽-닫힘.png", scene3, 1000, 242);
	door6->hide();

	auto door6_locked = true;
	auto door6_closed = true;

	door6->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (door6_locked) {

			showMessage("문이 잠겨있다.");

			if (orange_key->isHanded()) {

				door6_locked = false;
				showMessage("철커덕.");
			}
		}

		else if (door6_locked == false && door6_closed == true) {

			door6->setImage("images/문-오른쪽-열림.png");
			showMessage("문이 열렸다.");
			door6_closed = false;

		}

		else if (door6_locked == false && door6_closed == false) {

			scene4->enter();
		}

		return true;
		});

	//Scene_basement

	auto lab_cart = Object::create("images/lab_cart.png", scene_basement, 600, 50);
	auto red_button = Object::create("images/red_button.png", scene_basement, 800, 300);
	auto green_button = Object::create("images/green_button.png", scene_basement, 860, 300);
	auto blue_button = Object::create("images/blue_button.png", scene_basement, 920, 300);

	red_button->hide();
	green_button->hide();
	blue_button->hide();


	dish->setOnDropCallback([&](ObjectPtr object)->bool {
		dish_drop = true;
		dish->locate(scene_basement, 700, 320);

		if (dish_drop) {

			red_button->show();
			green_button->show();
			blue_button->show();

		}

		return true;

		});



	red_button->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		scene_end->enter();

		return true;
		});


	green_button->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {


		stair->hide();
		door6->show();
		scene2->enter();
		showMessage("방금 뭐였지?");

		return true;
		});

	blue_button->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		stair->hide();
		hidden_door->show();
		scene2->enter();
		showMessage("방금 뭐였지?");

		return true;
		
		});


	//Scene4

	auto man = Object::create("images/man.png", scene4, 1100, 50);
	man->setScale(0.8f);


	man->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		showMessage("자네 흥미롭구만. 걱정말게 모든 증거는 다 없앴으니. 자네도 이제 끝일세");
		scene_end->enter();
		return true;

		});

	//Scene_end

	auto end_page_button = Object::create("images/end.png", scene_end, 1100, 50);
	end_page_button->setScale(0.5f);

	auto final_page_button = Object::create("images/end.png", the_end, 1100, 50);
	final_page_button->setScale(0.5f);


	end_page_button->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		endGame();

		return true;
		});

	final_page_button->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		endGame();

		return true;
		});

	//Scene_final 

	auto unknown_man = Object::create("images/unknown_man.png", scene_final, 1100, 50);
	unknown_man->setScale(0.8f);

	auto back4 = Object::create("images/back.png", scene_final, 0, 620);

	back4->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene2_2->enter();
		return true;
		});

	unknown_man->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (syringe_fulled_1->isHanded()) {
			the_end->enter();
			return true;
		}

		else if (syringe_fulled_2->isHanded()) {

			scene_end->enter();
		}

		else {

			showMessage("나는 백신이 필요하다네,");

		}

		});

	startGame(main);

}



