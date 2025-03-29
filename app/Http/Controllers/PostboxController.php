<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\Models\PostboxEvents;

class PostboxController extends Controller
{
    /**
     * Display a listing of the resource.
     */
    public function index()
    {
        $latestEvent = PostboxEvents::latest()->first();
        $state = $latestEvent ? $latestEvent->status : 'empty';
        return response()->json(['state' => $state]);
    }

    /**
     * Store a newly created resource in storage.
     */
    public function store(Request $request, string $state)
    {
        // Validate the state
        if (!in_array($state, ['empty', 'full'])) {
            return response()->json(['error' => 'Invalid state'], 400);
        }

        // Store the state in the postbox_events model
        $postboxEvent = new PostboxEvents();
        $postboxEvent->status = $state;
        $postboxEvent->save();

        return response()->json(['message' => 'State updated successfully', 'state' => $state]);
    }

    /**
     * Display the specified resource.
     */
    public function show(string $id)
    {
        //
    }

    /**
     * Update the specified resource in storage.
     */
    public function update(Request $request, string $id)
    {
        //
    }

    /**
     * Remove the specified resource from storage.
     */
    public function destroy(string $id)
    {
        //
    }
}
