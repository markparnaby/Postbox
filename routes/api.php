<?php

use Illuminate\Http\Request;
use Illuminate\Support\Facades\Route;
use App\Http\Controllers\PostboxController;

Route::post('/postbox/state/{state}', [App\Http\Controllers\PostboxController::class, 'store']);
Route::get('/postbox', [App\Http\Controllers\PostboxController::class, 'index']);
